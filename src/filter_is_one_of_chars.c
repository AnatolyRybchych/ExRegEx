#include "filter_is_one_of_chars.h"
#include "filters.h"

typedef struct is_one_of_chars_data{
    int count;
    char *array;
}is_one_of_chars_data;


filter_t *filter_is_one_of_chars(char *chars){
    filter_t *result = malloc(sizeof(filter_t));

    result->data = malloc(sizeof(is_one_of_chars_data));
    ((is_one_of_chars_data*)result->data)->count = strlen(chars);
    ((is_one_of_chars_data*)result->data)->array = malloc(((is_one_of_chars_data*)result->data)->count);
    strcpy(((is_one_of_chars_data*)result->data)->array, chars);

    result->interface = &filters[FILTER_IS_ONE_OF_CHARS];
    result->is_active = true;

    return result;
}

void is_one_of_chars_on_first_step(filter_t *self, const proc_data_t *proc_data){

}

bool is_one_of_chars_on_step(filter_t *self, const proc_data_t *proc_data){
    self->is_active = false;
    is_one_of_chars_data *data = ((is_one_of_chars_data*)self->data);
    for(char *ch = data->array; ch < data->array + data->count; ch++){
        if(*ch == *proc_data->curr) return true;
    }
    return false;
}

match_t *is_one_of_chars_get_match(filter_t *self){
    return NULL;
}

void is_one_of_chars_free(filter_t *self){
    if(self == NULL) return;
    if(self->data){
        if(((is_one_of_chars_data*)self->data)->array) free(((is_one_of_chars_data*)self->data)->array);
        free(self->data);
    }
    
    free(self);
}
