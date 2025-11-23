#include "string_builder.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

strbld_t* strbld_new(size_t capacity) {
    char* string = malloc(capacity);
    string[0] = '\0';
    strbld_t* builder = malloc(sizeof(strbld_t));
    if(!builder) {
        fprintf(stderr, "strbld_new: Failed to allocate memory for string builder\n");
        return NULL;
    }
    builder->string = string;
    builder->capacity = capacity;
    builder->len = 0;
    return builder;
}

char* strbld_bld(strbld_t* bldr) {
    size_t len = bldr->len;
    char* str = malloc(len+1);
    memcpy(str, bldr->string, len);
    str[len] = '\0';
    return str;
}

bool strbld_insert(strbld_t* bldr, size_t index, char* target) {
    if(index > bldr->len) {
        fprintf(stderr, "strbld_insert: Out of bounds: %ld\n", index);
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
            fprintf(stderr, "strbld_insert: failed to reallocate string\n");
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

bool strbld_append(strbld_t* bld, char* target) {
    size_t target_len = strlen(target);
    if(target_len == 0) {
        return true;
    }
    if(target_len + bld->len+1 > bld->capacity) {
        size_t new_cpct = bld->capacity;
        while(new_cpct < bld->len + target_len+1) {
            if(new_cpct==0) {
                new_cpct = target_len+1;
            } else {
                new_cpct *= 2;
            }
        }
        void* new_str = realloc(bld->string, new_cpct);
        if(!new_str) {
            fprintf(stderr, "strbld_append: failed to reallocate string\n");
            return false;
        }
        bld->string = new_str;
        bld->capacity = new_cpct;
    }
    
    memcpy(bld->string + bld->len, target, target_len);
    bld->len += target_len;
    bld->string[bld->len] = '\0';
    return true;
}

char* format_str(char* fmt, va_list args) {
    va_list args_copy;
    va_copy(args_copy, args);
    int need = vsnprintf(NULL, 0, fmt, args_copy);
    va_end(args_copy);
    
    if(need < 0) {
        va_end(args);
        return NULL;
    }
    
    char* buffer = malloc(need + 1);
    if(!buffer) {
        va_end(args);
        return NULL;
    }
    
    int written = vsnprintf(buffer, need + 1, fmt, args);
    va_end(args);
    if(written != need) {
        free(buffer);
        return NULL;
    }
    return buffer;
}

bool strbld_appendf(strbld_t* bld, char* format, ...) {
    va_list args;
    va_start(args, format);
    return strbld_append(bld, format_str(format, args));
}

bool strbld_insertf(strbld_t* bld, size_t index, char* format, ...) {
    va_list args;
    va_start(args, format);
    return strbld_insert(bld, index, format_str(format, args));
}

bool strbld_push(strbld_t* bld, char target) {
    if(bld->len+1 > bld->capacity) {
        size_t new_cpt = bld->capacity * 2;
        void* new_str = realloc(bld->string, new_cpt);
        if(!new_str) {
            fprintf(stderr, "strbld_append: failed to reallocate string\n");
            return false;
        }
        bld->string = new_str;
        bld->capacity = new_cpt;
    }
    
    memcpy(bld->string + bld->len, &target, 1);
    bld->len += 1;
    bld->string[bld->len] = '\0';
    return true;
}

bool strbld_rm_range(strbld_t* bldr, size_t from, size_t to) {
    if(from >= bldr->len || to >= bldr->len) {
        fprintf(stderr, "strbld_rm_range: Out of bounds: %ld or %ld\n", from, to);
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
        fprintf(stderr, "strbld_rm: Out of bounds: %ld", position);
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
    char* result = malloc(len+1);
    if(!result) {
        fprintf(stderr, "strbld_subs: failed to allocate memory for result string\n");
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