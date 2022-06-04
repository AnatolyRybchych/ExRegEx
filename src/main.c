#include <stdio.h>
#include "ex_regex.h"

int main(int argc, char const *argv[])
{
    ex_regex_t *regex = ex_regex("[///q]");

    printf("expression:\n%s\n", regex->expr);






    ex_free_regex(regex);
    return 0;
}
