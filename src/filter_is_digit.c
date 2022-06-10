#include "filter_is_digit.h"
#include "filters.h"

filter_t *filter_is_digit(){
    filter_t *result = malloc(sizeof(filter_t));
    
    result->data = NULL;
    result->is_active = true;
    result->interface = &filters[FILTER_IS_DIGIT];

    return result;
}

void is_digit_on_first_step(filter_t *self, const proc_data_t *proc_data){}

bool is_digit_on_step(filter_t *self, const proc_data_t *proc_data){
    self->is_active = false;
    return *proc_data->curr >= '0' && *proc_data->curr <= '9';
}

match_t *is_digit_get_match(filter_t *self){}

void is_digit_free(filter_t *self){
    if(self == NULL) return;


    free(self);
}