#ifndef __FILTERS_H_
#define __FILTERS_H_

#include "filter.h"

enum filters{
    FILTER_IS_CHAR = 0,

    FILTERS_COUNT,
};

extern ifilter filters[FILTERS_COUNT];


#endif