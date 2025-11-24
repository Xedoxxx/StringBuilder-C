#ifndef STRING_BUILDER_H
#define STRING_BUILDER_H

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

/* struct for build strings */
typedef struct string_t {
  char *string;
  size_t capacity;
  size_t len;
} str_t;

/*
  Create new string builder.
  Return new string builder pointer or NULL in case of error.
 */
string_t *str_new(size_t capacity);

/*
  Get char by index in string builder.
  Return char by index.
 */
char str_get(string_t *bld, size_t index);

/*
  Get char by index in string builder with validate index.
  Return char by index or '\0' in case of error.
 */
char str_get_s(string_t *bld, size_t index);

/*
  Find char in string builder.
  Return index of found char or -1 in case of error.
 */
int str_find(string_t *bld, char to_find);

/*
  Create new string builder with the start string.
  Return new string builder pointer or NULL in case of error.
 */
string_t *str_from(char *str);

/*
  Build string from string_builder.
  Return builded string pointer.
 */
char *str_bld(string_t *bldr);

/*
  Append string to back of strbld.
  Return is successful.
 */
bool str_append(string_t *bld, char *target);

/*
  Append string to back of strbld.
  Return is successful.
 */
bool str_appendf(string_t *bld, char *format, ...);

/*
  Append char to back of string_t.
  Return is successful.
 */
bool str_push(string_t *bld, char target);

/*
  Insert string to string builder with index.
  Return is successful.
 */
bool str_insert(string_t *bldr, size_t index, char *target);

/*
  Insert string to string builder with index and format.
  Return is successful.
 */
bool str_insertf(string_t *bldr, size_t index, char *format, ...);

/*
  Clear string builder.
 */
void str_clear(string_t *bld);

/*
  Remove range string in string builder.
  Return is successful.
 */
bool str_rm_range(string_t *bldr, size_t from, size_t to);

/*
  Remove single char in string builder.
  Return is successful.
 */
bool str_rm(string_t *bldr, size_t position);

/*
  Substring.
  Return selected string or NULL in case of error.
 */
char *str_subs(string_t *bldr, size_t start, size_t end);

/*
  Free string builder and inside string.
 */
void str_free(string_t *bldr);

#endif