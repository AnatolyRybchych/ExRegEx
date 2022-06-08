#ifndef __FILTER_IS_CHAR_H_
#define __FILTER_IS_CHAR_H_
#include "filter.h"

void is_char_on_first_step(filter_t *self, const proc_data_t *proc_data);
bool is_char_on_step(filter_t *self, const proc_data_t *proc_data);
match_t *is_char_get_match(filter_t *self);
void is_char_free(filter_t *self);

#endif