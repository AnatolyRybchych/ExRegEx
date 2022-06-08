#ifndef __FILTER_IS_ONE_OF_CHARS_H_
#define __FILTER_IS_ONE_OF_CHARS_H_

#include "filter.h"

void is_one_of_chars_on_first_step(filter_t *self, const proc_data_t *proc_data);
bool is_one_of_chars_on_step(filter_t *self, const proc_data_t *proc_data);
match_t *is_one_of_chars_get_match(filter_t *self);
void is_one_of_chars_free(filter_t *self);

#endif