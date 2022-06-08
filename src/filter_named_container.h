#ifndef __FILTER_NAMED_CONTAINER_H_
#define __FILTER_NAMED_CONTAINER_H_

#include "filter.h"

void named_container_on_first_step(filter_t *self, const proc_data_t *proc_data);
bool named_container_on_step(filter_t *self, const proc_data_t *proc_data);
match_t *named_container_get_match(filter_t *self);
void named_container_free(filter_t *self);

#endif