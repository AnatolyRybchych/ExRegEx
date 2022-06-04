#include "filter.h"

filter_list_t *filter_list(){
    filter_list_t *result = malloc(sizeof(filter_list_t));
    memset(result, 0, sizeof(filter_list_t));

    return result;
}

void free_filter_list(filter_list_t **list_ptr){
    if(list_ptr == NULL) return;
    if(*list_ptr == NULL) return;

    for(int filter = 0; filter < list_ptr[0]->count; filter++)
        list_ptr[0]->data[filter]->interface->free(list_ptr[0]->data[filter]);

    if(list_ptr[0]->data)   free(list_ptr[0]->data);

    free(*list_ptr);
    *list_ptr = NULL; 
}

void filter_list_add(filter_list_t *list, const ifilter *interface, const ex_regex_t *regex){
    list->data = realloc(list->data, ++list->count);
    list->data[list->count - 1] = interface->init(regex);
}
