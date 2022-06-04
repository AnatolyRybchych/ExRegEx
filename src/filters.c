#include "filters.h"

static void is_char_on_first_step(filter_t *self, const proc_data_t *proc_data);
static bool is_char_on_step(filter_t *self, const proc_data_t *proc_data);
static match_t *is_char_get_match(filter_t *self);
static void is_char_free(filter_t *self);


enum filters{
    FILTER_IS_CHAR = 0,

    FILTERS_COUNT,
};

ifilter filters[FILTERS_COUNT] = {
    [FILTER_IS_CHAR] = {
        .on_first_step = is_char_on_first_step,
        .on_step = is_char_on_step,
        .get_match = is_char_get_match,
        .free = is_char_free,
    },
};



#pragma region is_char

typedef struct is_char_data{
    char ch;
}is_char_data;

filter_t *filter_is_char(char ch){
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

static void is_char_on_first_step(filter_t *self, const proc_data_t *proc_data){}

static bool is_char_on_step(filter_t *self, const proc_data_t *proc_data){
    self->is_active = false;
    if(*proc_data->curr == ((is_char_data*)self->data)->ch)
        return true;
    else
        return false;
}

static match_t *is_char_get_match(filter_t *self){}

static void is_char_free(filter_t *self){
    if(self == NULL) return;

    if(self->data) free(self->data);
}

#pragma endregion