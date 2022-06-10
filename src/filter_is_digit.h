#ifndef __FILTER_IS_DIGIT_H_
#define __FILTER_IS_DIGIT_H_
#include "filter.h"

void is_digit_on_first_step(filter_t *self, const proc_data_t *proc_data);
bool is_digit_on_step(filter_t *self, const proc_data_t *proc_data);
match_t *is_digit_get_match(filter_t *self);
void is_digit_free(filter_t *self);

#endif
