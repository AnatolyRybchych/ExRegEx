#ifndef __PROC_DATA_H_
#define __PROC_DATA_H_
#include <malloc.h>
#include <stdbool.h>
#include <string.h>

typedef struct proc_data_t proc_data_t;

proc_data_t *proc_data(char *beg, char *end);
void free_proc_data(proc_data_t **data);


struct proc_data_t{
    char *beg;
    char *end;
    char *curr;
};


#endif