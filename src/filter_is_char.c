#include "filter_is_char.h"
#include "filters.h"


typedef struct is_char_data{
    char ch;
}is_char_data;


filter_t *filter_is_char(const char ch){
    filter_t *result = malloc(sizeof(filter_t));

    is_char_data data ={
        .ch = ch,
    };
    result->data = malloc(sizeof(is_char_data));
    (*(is_char_data*)result->data) = data;

    result->interface = &filters[FILTER_IS_CHAR];
    result->is_active = true;

    return result;
}

void is_char_on_first_step(filter_t *self, const proc_data_t *proc_data){}

bool is_char_on_step(filter_t *self, const proc_data_t *proc_data){
    self->is_active = false;
    if(*proc_data->curr == ((is_char_data*)self->data)->ch)
        return true;
    else
        return false;
}

match_t *is_char_get_match(filter_t *self){
    return NULL;
}

void is_char_free(filter_t *self){
    if(self == NULL) return;

    if(self->data) free(self->data);
    free(self);
}

