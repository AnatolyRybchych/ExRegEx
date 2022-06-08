#ifndef __FILTERS_H_
#define __FILTERS_H_

#include "filter.h"

enum filters{
    FILTER_IS_CHAR = 0,
    FILTER_IS_ONE_OF_CHARS = 1,
    FILTER_NAMED_CONTAINER = 2,

    FILTERS_COUNT,
};

extern ifilter filters[FILTERS_COUNT];

filter_t *filter_is_char(char ch);
filter_t *filter_is_one_of_chars(char *chars);




#endif