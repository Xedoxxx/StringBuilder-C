#include "string_builder.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

strbld_t* strbld_new(size_t capacity) {
    char* string = (char*) malloc(capacity);
    string[0] = '\0';
    strbld_t* builder = (strbld_t*) malloc(sizeof(strbld_t));
    if(!builder) {
        fprintf(stderr, "strbld_t_new: Failed to allocate memory for string builder");
        return NULL;
    }
    builder->string = string;
    builder->capacity = capacity;
    builder->len = 0;
    return builder;
}

char* strbld_bld(strbld_t* bldr) {
    size_t len = strlen(bldr->string);
    char* str = (char*) malloc(len+1);
    memcpy(str, bldr->string, len);
    str[len] = '\0';
    return str;
}

bool strbld_insert(strbld_t* bldr, size_t index, const char* target) {
    if(index > bldr->len) {
        fprintf(stderr, "strbld_t_insert: Out od bounds: %ld", index);
        return false;
    }
    size_t target_len = strlen(target);
    if(target_len == 0) {
        return true;
    }
    if(target_len + bldr->len+1 > bldr->capacity) {
        size_t new_cpct = bldr->capacity;
        while(new_cpct < bldr->len + target_len+1) {
            if(new_cpct==0) {
                new_cpct = target_len+1;
            } else {
                new_cpct *= 2;
            }
        }
        void* new_str = realloc(bldr->string, new_cpct);
        if(!new_str) {
            fprintf(stderr, "strbld_t_insert: failed to reallocate string");
            return false;
        }
        bldr->string = new_str;
        bldr->capacity = new_cpct;
    }
    
    if(index != bldr->len) {
        memmove(bldr->string + index + target_len, bldr->string + index, bldr->len - index);
    }
    memcpy(bldr->string + index, target, target_len);
    bldr->len += target_len;
    bldr->string[bldr->len] = '\0';
    return true;
}

bool strbld_rm_range(strbld_t* bldr, size_t from, size_t to) {
    if(from >= bldr->len || to >= bldr->len) {
        fprintf(stderr, "strbld_t_rm_range: Out of bounds: %ld or %ld", from, to);
        return false;
    }
    if(from > to) {
        size_t buffer = from;
        from = to;
        to = buffer;
    }
    char* str = bldr->string;
    memmove(str+from, str+to, bldr->len-to);
    bldr->len -= to-from;
    str[bldr->len] = '\0';
    return true;
}

bool strbld_rm(strbld_t* bldr, size_t position) {
    if(position >= bldr->len) {
        fprintf(stderr, "strbld_t_rm: Out of bounds: %ld", position);
        return false;
    }
    char* str = bldr->string;
    if(position+1 < bldr->len) {
        memmove(str+position, str+position+1, bldr->len-position-1);
    }
    bldr->len -= 1;
    str[bldr->len] = '\0';
    return true;
}

char* strbld_subs(strbld_t* bldr, size_t start, size_t end) {
    if(start > end) {
        size_t buffer = start;
        start = end;
        end = buffer;
    }
    size_t len = end - start;
    char* result = (char*) malloc(len+1);
    if(!result) {
        fprintf(stderr, "strbld_t_subs: failed to allocate memory for result string");
        return NULL;
    }
    memcpy(result, bldr->string+start, len);
    result[len] = '\0';
    return result;
}

void strbld_free(strbld_t* bldr) {
    free(bldr->string);
    free(bldr);
}