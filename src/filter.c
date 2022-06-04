#include "filter.h"

filter_list_t *filter_list(){
    filter_list_t *result = malloc(sizeof(filter_list_t));
    memset(result, 0, sizeof(filter_list_t));

    return result;
}

void free_filter_list(filter_list_t **list_ptr){
    if(list_ptr == NULL) return;
    if(*list_ptr == NULL) return;

    if(list_ptr[0]->data)   free(list_ptr[0]->data);

    free(*list_ptr);
    *list_ptr = NULL; 
}