#include "ex_regex.h"
#include "filter.h"

ex_regex_t *ex_regex(const char *expression){
    ex_regex_t *result = malloc(sizeof(ex_regex_t));

    result->proc_data = NULL;

    result->filters = filter_list();

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

    free_proc_data(regex->proc_data);

    free_filter_list(&regex->filters);

    free(regex);
}

void ex_compile_regex(ex_regex_t *regex){
    if(regex == NULL) return;

    
}


void ex_regex_matches(ex_regex_t *regex, const char *text){

}