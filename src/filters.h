#ifndef __FILTERS_H_
#define __FILTERS_H_

#include "filter.h"

filter_t *filter_is_char(char ch);
filter_t *filter_is_one_of_chars(char *chars);


#endif