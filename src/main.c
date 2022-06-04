#include <stdio.h>
#include "ex_regex.h"


void print_matches(const matches_list_t *matches, int tabs){
    if(matches == NULL) return;

    for(int i = 0; i < matches->count; i++){
        for(int j = 0; j < tabs; j++) printf("    ");
        printf("match {index = %d, name = \"%s\"}:\n", matches->matches[i]->start_index, matches->matches[i]->name);
        for(int j = 0; j < tabs; j++) printf("    ");
        printf("\"%s\"\n", matches->matches[i]->str);
        print_matches(matches->matches[i]->inner_matches, tabs + 1);
        printf("\n");
    }
}


int main(int argc, char const *argv[])
{
    ex_regex_t *regex = ex_regex("gs");
    ex_compile_regex(regex);

    printf("expression:\"%s\"\n\n", regex->expr);

    ex_regex_matches(regex, "qwegsfd");

    if(regex->matches->count == 0){
        printf("no matches\n");
    }

    print_matches(regex->matches, 0);


    ex_free_regex(regex);
    return 0;
}
