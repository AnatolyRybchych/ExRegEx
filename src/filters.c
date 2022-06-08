#include "filters.h"
#include "filter_is_char.h"
#include "filter_is_one_of_chars.h"
#include "filter_named_container.h"

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
    [FILTER_NAMED_CONTAINER] = {
        .on_first_step = named_container_on_first_step,
        .on_step = named_container_on_step,
        .get_match = named_container_get_match,
        .free = named_container_free,
    },
};


