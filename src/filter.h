#ifndef __FILTER_H_
#define __FILTER_H_
#include <stdbool.h>

#include "match.h"
#include "ex_regex.h"

typedef struct filter_t filter_t;
typedef struct ifilter ifilter;
typedef struct filter_list_t filter_list_t;

struct filter_t{
    bool is_active;//false if required to move to nex filter
    void *data;
    const ifilter *interface;
};

struct ifilter{
    void (*on_first_step)(filter_t *self, const proc_data_t *proc_data);
    bool (*on_step)(filter_t *self, const proc_data_t *proc_data);//returns true, if matched, 
    match_t *(*get_match)(filter_t *self);//should return NULL if have not
    void (*free)(filter_t *self);
};

filter_list_t *filter_list();
void filter_list_add(filter_list_t *list, filter_t *filter, const ex_regex_t *regex);
void free_filter_list(filter_list_t **list_ptr);

struct filter_list_t{
    int count;
    filter_t **data;
};

#endif