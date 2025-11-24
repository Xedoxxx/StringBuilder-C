#include "string_builder.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main() {
    printf("\033[34mTesting str_t...\033[0m\n");
    
    /* Create string builder */
    str_t* bld = str_from("Hello, world!");
    assert(bld);
    
    /* build string */
    str_insertf(bld, 0, "%s ", "No");
    str_push(bld, ')');
    str_rm_range(bld, 3, 10); /* Remove "Hello" */
    
    /* print info about builded string */
    char* subs = str_subs(bld, 0, 2);
    printf("Builded string: %s\n", str_bld(bld));
    printf("Substring: %s\n", subs);
    free(subs);
    
    /* Search index by char */
    int index = str_find(bld, 'o');
    printf("'o' in %d index\n", index);
    
    /* Free string builder*/
    str_free(bld);
    
    printf("\033[33mSuccessful testing str_t!\033[0m\n");
}