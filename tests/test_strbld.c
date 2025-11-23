#include "string_builder.h"
#include <stdio.h>
#include <assert.h>

int main() {
    printf("\033[34mTesting strbld_t...\033[0m\n");
    /* Create string builder */
    strbld_t* bld = strbld_new(30);
    assert(bld);
    
    /* build string */
    strbld_appendf(bld, "%s, %s!", "Hello", "world");
    strbld_insertf(bld, 0, "%s ", "No");
    strbld_push(bld, ')');
    strbld_rm_range(bld, 3, 10);
    
    /* print info about builded string */
    printf("Builded string: %s\n", strbld_bld(bld));
    char* subs = strbld_subs(bld, 0, 2);
    printf("Substring: %s\n", subs);
    
    printf("\033[33mSuccessful testing strbld_t!\033[0m\n");
}