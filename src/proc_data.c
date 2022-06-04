#include "proc_data.h"

proc_data_t *proc_data(const char *beg, const char *end){
    proc_data_t *result = malloc(sizeof(proc_data_t));
    memset(result, 0, sizeof(proc_data_t));

    result->beg = beg;
    result->end = end;
    result->curr = beg;


    return result;
}

void free_proc_data(proc_data_t **data){
    if(data == NULL) return;
    if(*data == NULL) return;



    free(*data);
    *data = NULL;
}

bool proc_data_next(proc_data_t *data){
    return ++data->curr < data->end;
}
