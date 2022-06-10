#include "filter_named_container.h"
#include "filters.h"

typedef struct named_container_data{
    char *name;
    int match_len;
    int match_start;
    char *match;
    filter_t *filter;
}named_container_data;

filter_t *filter_named_container(const char *name, filter_t *filter){
    filter_t *result = malloc(sizeof(filter_t));

    result->is_active = true;
    result->interface = &filters[FILTER_NAMED_CONTAINER];
    result->data = malloc(sizeof(named_container_data));
    named_container_data *data = (named_container_data*)result->data;
    int name_len = strlen(name);

    data->name = malloc(name_len + 1);
    strcpy(data->name, name);
    data->filter = filter;

    data->match = malloc(1);
    data->match[0] = 0;
    data->match_len = 1;
    data->match_start = 0;

    return result;
}

void named_container_on_first_step(filter_t *self, const proc_data_t *proc_data){
    named_container_data *data = (named_container_data*)self->data;

    data->match_start = proc_data->curr - proc_data->beg;
    data->filter->interface->on_first_step(data->filter, proc_data);
}

bool named_container_on_step(filter_t *self, const proc_data_t *proc_data){
    named_container_data *data = (named_container_data*)self->data;

    if(data->filter->interface->on_step(data->filter, proc_data)){
        data->match = realloc(data->match, ++data->match_len);
        data->match[data->match_len - 2] = *proc_data->curr;
        data->match[data->match_len - 1] = 0;

        return true;
    }
    else{
        data->match = realloc(data->match, data->match_len = 1);
        data->match[0] = 0;
        data->match_start = -1;

        return false;
    }
}

match_t *named_container_get_match(filter_t *self){
    named_container_data *data = (named_container_data*)self->data;

    match_t *result = match(data->name, data->match, data->match_start);
    match_t *child_match = data->filter->interface->get_match(data->filter);
    if(child_match){
        matches_list_add(result->inner_matches, child_match);
    }
    
    return result;
}

void named_container_free(filter_t *self){
    if(self == NULL) return;

    if(self->data){
        named_container_data *data = (named_container_data*)self->data;
        if(data->name) free(data->name);
        if(data->match) free(data->match);
        data->filter->interface->free(data->filter);
        

        free(data);
    }
    free(self);
}
