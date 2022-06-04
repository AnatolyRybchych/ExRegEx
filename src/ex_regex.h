#ifndef __EX_REGEX_H_
#define __EX_REGEX_H_
#include <string.h>
#include <malloc.h>

#include "proc_data.h"
#include "filter.h"

typedef struct ex_regex_t ex_regex_t;


ex_regex_t *ex_regex(const char *expression);

void ex_free_regex(ex_regex_t *regex);


struct ex_regex_t{
    int expr_len;
    char *expr;
    proc_data_t *proc_data;
    filter_list_t *filters;
};



#endif