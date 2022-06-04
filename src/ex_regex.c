#include "ex_regex.h"
#include "filters.h"

#include <stdio.h>

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

    for(int ch = 0; ch < regex->expr_len; ch++){
        filter_list_add(regex->filters, filter_is_char(regex->expr[ch]), regex);
    }
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

        do{
            curr_match = realloc(curr_match, ++curr_match_len + 1);
            curr_match[curr_match_len - 1] = *data->curr;
            curr_match[curr_match_len] = 0;
            if(curr_filter->interface->on_step(curr_filter, data)){
                if(curr_filter->is_active == false){
                    if(filter_next(regex, &curr_filter, &curr_filter_id) == false){
                        matches_list_add(regex->matches, match("root", curr_match, regex->proc_data->curr - regex->proc_data->beg));
                        break;
                    }
                }
            }
            else{
                break;
            }
            
            
        } while (proc_data_next(data));

        curr_match = realloc(curr_match, 0);
        free_proc_data(&data);
    } while (proc_data_next(regex->proc_data));
}