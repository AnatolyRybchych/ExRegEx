#include "ex_regex.h"
#include "filters.h"

#include <stdio.h>
#include <assert.h>

static void ex_regex_matches_unsafe(ex_regex_t *regex);
static bool filter_next(ex_regex_t *regex, filter_t **filter, int *filter_id);

ex_regex_t *ex_regex(const char *expression){
    ex_regex_t *result = malloc(sizeof(ex_regex_t));

    result->proc_data = NULL;

    result->filters = filter_list();
    result->matches = matches_list();

    result->expr_len = strlen(expression);
    result->expr = malloc(sizeof(char) * result->expr_len + 1);
    strcpy(result->expr, expression);

    return result;
}

void ex_free_regex(ex_regex_t *regex){
    if(regex == NULL) return;

    regex->expr_len = 0;
    if(regex->expr) free(regex->expr);
    regex->expr = NULL;

    free_proc_data(&regex->proc_data);
    free_matches_list(&regex->matches);
    free_filter_list(&regex->filters);

    free(regex);
}

void ex_compile_regex(ex_regex_t *regex){
    if(regex == NULL) return;

    char prev_char = 0;
    bool one_of = false;
    int one_of_start = 0;

    for(int ch = 0; ch < regex->expr_len; ch++){
        char curr = regex->expr[ch];
        if(one_of){
            if(curr == ']' && prev_char != '\\'){
                one_of = false;
                char *one_of_arr = alloca(ch - one_of_start + 1);
                sprintf(one_of_arr, "%.*s", ch - one_of_start , regex->expr + one_of_start);
                filter_list_add(regex->filters, filter_is_one_of_chars(one_of_arr), regex);
            }
        }
        else{
            if(curr == '[' && prev_char != '\\'){
                one_of = true;
                one_of_start = ch + 1;
            }
            else{
                filter_list_add(regex->filters, filter_is_char(curr), regex);
            }
        }

        prev_char = curr;
    }
    assert(!one_of && "missing expected ']'");
}


void ex_regex_matches(ex_regex_t *regex, const char *text){
    if(regex == NULL) return;
    if(regex->filters->count == 0) return;


    free_proc_data(&regex->proc_data);
    regex->proc_data = proc_data(text, text + strlen(text));
    if(regex->proc_data->beg == regex->proc_data->end);

    ex_regex_matches_unsafe(regex);
}

static bool filter_next(ex_regex_t *regex, filter_t **filter, int *filter_id){
    if(*filter == NULL) {
        filter[0] = *regex->filters->data;
        *filter_id = 0;
        filter[0]->interface->on_first_step(filter[0], regex->proc_data);
        return true;
    }
    else if(*filter_id < regex->filters->count - 1){
        filter[0] = regex->filters->data[++filter_id[0]];
        filter[0]->interface->on_first_step(filter[0], regex->proc_data);
        return true;
    }
    else{
        *filter = *regex->filters->data;
        filter_id[0] = 0;
        filter[0]->interface->on_first_step(filter[0], regex->proc_data);
        return false;
    }
}

static void ex_regex_matches_unsafe(ex_regex_t *regex){
    do{
        if(regex->proc_data->curr == regex->proc_data->end) return;
        proc_data_t *data = proc_data(regex->proc_data->curr, regex->proc_data->end);

        filter_t *curr_filter = NULL;
        int curr_filter_id = 0;
        filter_next(regex, &curr_filter, &curr_filter_id);

        int curr_match_len = 0;
        char *curr_match = realloc(NULL, curr_match_len + 1);
        curr_match[curr_match_len] = 0;

        matches_list_t *child_matches = matches_list();  

        do{
            curr_match = realloc(curr_match, ++curr_match_len + 1);
            curr_match[curr_match_len - 1] = *data->curr;
            curr_match[curr_match_len] = 0;
            if(curr_filter->interface->on_step(curr_filter, data)){
                if(curr_filter->is_active == false){
                    match_t *m = curr_filter->interface->get_match(curr_filter);
                    if(m) matches_list_add(child_matches, m);
                    if(filter_next(regex, &curr_filter, &curr_filter_id) == false){
                        match_t *new_match =  match("root", curr_match, regex->proc_data->curr - regex->proc_data->beg);
                        free_matches_list(&new_match->inner_matches);
                        new_match->inner_matches = child_matches;
                        child_matches = NULL;
                        matches_list_add(regex->matches, new_match);
                        break;
                    }
                }
            }
            else{
                break;
            }
            
            
        } while (proc_data_next(data));
        free_matches_list(&child_matches);
        curr_match = realloc(curr_match, 0);
        free_proc_data(&data);
    } while (proc_data_next(regex->proc_data));
}