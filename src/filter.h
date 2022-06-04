#ifndef __FILTER_H_
#define __FILTER_H_
#include <stdbool.h>
#include "ex_regex.h"

typedef struct filter_t filter_t;
typedef struct ifilter ifilter;
typedef struct filter_list_t filter_list_t;

struct filter_t{
    bool is_active;
    void *data;
    const ifilter *const interface;
};

struct ifilter{
    filter_t *(*init)(const ex_regex_t *regex);
    void (*free)(filter_t *filter);
};

filter_list_t *filter_list();
void free_filter_list(filter_list_t **list_ptr);

struct filter_list_t{
    int count;
    filter_t **data;
};

#endif