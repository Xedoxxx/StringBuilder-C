#ifndef STRING_BUILDER_H
#define STRING_BUILDER_H

#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>

/* struct for build strings */
typedef struct strbld_t {
    char* string;
    size_t capacity;
    size_t len;
} strbld_t;

/* 
  Create new string builder.
  Return new string builder pointer or NULL in case of error.
 */
strbld_t *strbld_new(size_t capacity);

/*
  Build string from string_builder.
  Return builded string pointer.
 */
char *strbld_bld(strbld_t *bldr);

/* 
  Append string to back of strbld.
  Return is successful.
 */
bool strbld_append(strbld_t* bld, char* target);

/* 
  Append string to back of strbld.
  Return is successful.
 */
bool strbld_appendf(strbld_t* bld, char* format, ...);

/* 
  Append char to back of strbld_t.
  Return is successful.
 */
bool strbld_push(strbld_t* bld, char target);

/*
  Insert string to string builder with index.
  Return is successful.
 */
bool strbld_insert(strbld_t *bldr, size_t index, char *target);

/*
  Insert string to string builder with index and format.
  Return is successful.
 */
bool strbld_insertf(strbld_t* bldr, size_t index, char* format, ...);

/*
  Remove range string in string builder.
  Return is successful.
 */
bool strbld_rm_range(strbld_t *bldr, size_t from, size_t to);

/*
  Remove single char in string builder.
  Return is successful.
 */
bool strbld_rm(strbld_t *bldr, size_t position);

/*
  Substring.
  Return selected string or NULL in case of error.
 */
char* strbld_subs(strbld_t* bldr, size_t start, size_t end);

/*
  Free string builder and inside string.
 */
void strbld_free(strbld_t *bldr);

#endif