#ifndef __EX_REGEX_H_
#define __EX_REGEX_H_
#include <string.h>
#include <malloc.h>

#include "proc_data.h"
#include "match.h"

typedef struct ex_regex_t ex_regex_t;
typedef struct filter_list_t filter_list_t;


ex_regex_t *ex_regex(const char *expression);
void ex_free_regex(ex_regex_t *regex);

void ex_compile_regex(ex_regex_t *regex);

void ex_regex_matches(ex_regex_t *regex, const char *text);

struct ex_regex_t{
    int expr_len;
    char *expr;
    proc_data_t *proc_data;
    filter_list_t *filters;
    matches_list_t *matches;
};



#endif