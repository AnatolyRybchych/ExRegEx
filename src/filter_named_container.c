#include "filter_named_container.h"

typedef struct named_container_data{
    char ch;
}named_container_data;


filter_t *filter_named_container(){
    filter_t *result = malloc(sizeof(filter_t));

    return result;
}

void named_container_on_first_step(filter_t *self, const proc_data_t *proc_data){}

bool named_container_on_step(filter_t *self, const proc_data_t *proc_data){

}

match_t *named_container_get_match(filter_t *self){
    return NULL;
}

void named_container_free(filter_t *self){
    if(self == NULL) return;

    free(self);
}
