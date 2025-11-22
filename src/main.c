#include "string_builder.h"
#include <stdio.h>

int main() {
    strbld* bld = strbld_new(30);
    strbld_insert(bld, 0, "Hello, world!");
    strbld_insert(bld, 0, "No ");
    strbld_rm_range(bld, 3, 10);
    printf("Builded string: %s\n", strbld_bld(bld));
    
    char* subs = strbld_subs(bld, 0, 2);
    printf("Substring: %s\n", subs);
}