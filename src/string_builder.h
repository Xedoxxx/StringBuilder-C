#ifndef STRING_BUILDER_H
#define STRING_BUILDER_H

#include <stddef.h>
#include <stdbool.h>

/* struct for build strings */
typedef struct string_builder {
    char* string;
    size_t capacity;
    size_t len;
} strbld;

/* 
  Create new string builder.
  Return new string builder pointer or NULL in case of error.
 */
strbld *strbld_new(size_t capacity);

/*
  Build string from string_builder.
  Return builded string pointer.
 */
char *strbld_bld(strbld *bldr);

/*
  Insert string to string builder with index.
  Return is successful.
 */
bool strbld_insert(strbld *bldr, size_t index, const char *target);

/*
  Remove range string in string builder.
  Return is successful.
 */
bool strbld_rm_range(strbld *bldr, size_t from, size_t to);

/*
  Remove single char in string builder.
  Return is successful.
 */
bool strbld_rm(strbld *bldr, size_t position);

/*
  Substring.
  Return selected string or NULL in case of error.
 */
char* strbld_subs(strbld* bldr, size_t start, size_t end);

/*
  Free string builder and inside string.
 */
void strbld_free(strbld *bldr);

#endif