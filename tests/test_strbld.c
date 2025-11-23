#include "string_builder.h"
#include <stdio.h>
#include <assert.h>

int main() {
    printf("\033[34mTesting strbld_t...\033[0m\n");
    strbld_t* bld = strbld_new(30);
    assert(bld);
    strbld_insert(bld, 0, "Hello, world!");
    strbld_insert(bld, 0, "No ");
    strbld_rm_range(bld, 3, 10);
    printf("Builded string: %s\n", strbld_bld(bld));
    
    char* subs = strbld_subs(bld, 0, 2);
    printf("Substring: %s\n", subs);
    printf("\033[33mSuccessful testing strbld_t!\033[0m\n");
}