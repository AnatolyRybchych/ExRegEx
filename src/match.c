#include "match.h"

match_t *match(const char *name, const char *str, int start_index){
    match_t *result = malloc(sizeof(match_t));

    result->start_index = start_index;

    result->str_len = strlen(str);
    result->str = malloc(result->str_len + 1);
    strcpy(result->str, str);

    result->name_len = strlen(name);
    result->name = malloc(result->name_len + 1);
    strcpy(result->name, name);

    result->inner_matches = matches_list();

    return result;
}

void free_match(match_t **match){
    if(match == NULL) return;
    if(*match == NULL) return;

    if(match[0]->str) free(match[0]->str);
    if(match[0]->name) free(match[0]->name);

    free_matches_list(&match[0]->inner_matches);

    free(*match);
    *match = NULL;
}

matches_list_t *matches_list(){
    matches_list_t *result = malloc(sizeof(matches_list_t));
    memset(result, 0, sizeof(matches_list_t));
    return result;
}

void free_matches_list(matches_list_t **list_ptr){
    if(list_ptr == NULL) return;
    if(*list_ptr == NULL) return;

    for(int match = 0; match < list_ptr[0]->count; match++){
        free_match(list_ptr[0]->matches + match);
    }

    free(*list_ptr);
    *list_ptr = NULL;
}

void matches_list_add(matches_list_t *list, match_t /*will freed*/ *match){
    list->matches = realloc(list->matches, ++list->count * sizeof(match_t*));
    list->matches[list->count - 1] = match;
}
