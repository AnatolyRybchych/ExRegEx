#include "filters.h"

static void is_char_on_first_step(filter_t *self, const proc_data_t *proc_data);
static bool is_char_on_step(filter_t *self, const proc_data_t *proc_data);
static match_t *is_char_get_match(filter_t *self);
static void is_char_free(filter_t *self);

static void is_one_of_chars_on_first_step(filter_t *self, const proc_data_t *proc_data);
static bool is_one_of_chars_on_step(filter_t *self, const proc_data_t *proc_data);
static match_t *is_one_of_chars_get_match(filter_t *self);
static void is_one_of_chars_free(filter_t *self);

enum filters{
    FILTER_IS_CHAR = 0,
    FILTER_IS_ONE_OF_CHARS = 1,

    FILTERS_COUNT,
};

ifilter filters[FILTERS_COUNT] = {
    [FILTER_IS_CHAR] = {
        .on_first_step = is_char_on_first_step,
        .on_step = is_char_on_step,
        .get_match = is_char_get_match,
        .free = is_char_free,
    },
    [FILTER_IS_ONE_OF_CHARS] = {
        .on_first_step = is_one_of_chars_on_first_step,
        .on_step = is_one_of_chars_on_step,
        .get_match = is_one_of_chars_get_match,
        .free = is_one_of_chars_free,
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

static match_t *is_char_get_match(filter_t *self){
    return NULL;
}

static void is_char_free(filter_t *self){
    if(self == NULL) return;

    if(self->data) free(self->data);
    free(self);
}

#pragma endregion

#pragma region is_one_of_chars

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

static void is_one_of_chars_on_first_step(filter_t *self, const proc_data_t *proc_data){

}

static bool is_one_of_chars_on_step(filter_t *self, const proc_data_t *proc_data){
    self->is_active = false;
    is_one_of_chars_data *data = ((is_one_of_chars_data*)self->data);
    for(char *ch = data->array; ch < data->array + data->count; ch++){
        if(*ch == *proc_data->curr) return true;
    }
    return false;
}

static match_t *is_one_of_chars_get_match(filter_t *self){
    return NULL;
}

static void is_one_of_chars_free(filter_t *self){
    if(self == NULL) return;
    if(self->data){
        if(((is_one_of_chars_data*)self->data)->array) free(((is_one_of_chars_data*)self->data)->array);
        free(self->data);
    }
    
    free(self);
}


#pragma endregion

