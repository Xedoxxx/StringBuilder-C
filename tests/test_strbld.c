#include "string_builder.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main() {
    printf("\033[34mTesting strbld_t...\033[0m\n");
    
    /* Create string builder */
    strbld_t* bld = strbld_from("Hello, world!");
    assert(bld);
    
    /* build string */
    strbld_insertf(bld, 0, "%s ", "No");
    strbld_push(bld, ')');
    strbld_rm_range(bld, 3, 10); /* Remove "Hello" */
    
    /* print info about builded string */
    char* subs = strbld_subs(bld, 0, 2);
    printf("Builded string: %s\n", strbld_bld(bld));
    printf("Substring: %s\n", subs);
    free(subs);
    
    /* Search index by char */
    int index = strbld_find(bld, 'o');
    printf("'o' in %d index\n", index);
    
    /* Free string builder*/
    strbld_free(bld);
    
    printf("\033[33mSuccessful testing strbld_t!\033[0m\n");
}