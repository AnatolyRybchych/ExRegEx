#ifndef __MATCH_H_
#define __MATCH_H_

#include <malloc.h>
#include <string.h>

typedef struct match_t match_t;
typedef struct matches_list_t matches_list_t;


match_t *match(const char *name, const char *str, int start_index);
void free_match(match_t **match);

struct match_t{
    int start_index;
    int str_len;
    char *str;

    int name_len;
    char *name;

    matches_list_t *inner_matches;
};

matches_list_t *matches_list();
void matches_list_add(matches_list_t *list, match_t /*will freed*/ *match);
void free_matches_list(matches_list_t **list_ptr);

struct matches_list_t{
    int count;
    match_t **matches;
};

#endif