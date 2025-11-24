#ifndef STRING_BUILDER_H
#define STRING_BUILDER_H

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

/* struct for build strings */
typedef struct str_t {
  char *string;
  size_t capacity;
  size_t len;
} str_t;

/*
  Create new string builder.
  Return new string builder pointer or NULL in case of error.
 */
str_t *str_new(size_t capacity);

/*
  Get char by index in string builder.
  Return char by index.
 */
char str_get(str_t *bld, size_t index);

/*
  Get char by index in string builder with validate index.
  Return char by index or '\0' in case of error.
 */
char str_get_s(str_t *bld, size_t index);

/*
  Find char in string builder.
  Return index of found char or -1 in case of error.
 */
int str_find(str_t *bld, char to_find);

/*
  Create new string builder with the start string.
  Return new string builder pointer or NULL in case of error.
 */
str_t *str_from(char *str);

/*
  Build string from string_builder.
  Return builded string pointer.
 */
char *str_bld(str_t *bldr);

/*
  Append string to back of strbld.
  Return is successful.
 */
bool str_append(str_t *bld, char *target);

/*
  Append string to back of strbld.
  Return is successful.
 */
bool str_appendf(str_t *bld, char *format, ...);

/*
  Append char to back of str_t.
  Return is successful.
 */
bool str_push(str_t *bld, char target);

/*
  Insert string to string builder with index.
  Return is successful.
 */
bool str_insert(str_t *bldr, size_t index, char *target);

/*
  Insert string to string builder with index and format.
  Return is successful.
 */
bool str_insertf(str_t *bldr, size_t index, char *format, ...);

/*
  Clear string builder.
 */
void str_clear(str_t *bld);

/*
  Remove range string in string builder.
  Return is successful.
 */
bool str_rm_range(str_t *bldr, size_t from, size_t to);

/*
  Remove single char in string builder.
  Return is successful.
 */
bool str_rm(str_t *bldr, size_t position);

/*
  Substring.
  Return selected string or NULL in case of error.
 */
char *str_subs(str_t *bldr, size_t start, size_t end);

/*
  Free string builder and inside string.
 */
void str_free(str_t *bldr);

#endif