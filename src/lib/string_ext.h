#pragma once
#ifndef H_STRING_EXT_INCLUDED
#define H_STRING_EXT_INCLUDED 

#include <stddef.h>

/**
 * @brief strrep - create a string that repeats "str" n times
 * @param str - string to repeat
 * @param n - number of repetitions
 * @return {char *} - the repeated string
 **/
char * strrep(const char * str, size_t n);

/**
 * @brief chrrep - create a string that repeats the character 'ch' n times
 * @param ch - character to repeat
 * @param n - number of repetitions
 * @return {char *} - the repeated string
 **/
char * chrrep(const char ch, size_t n);

/**
 * @brief strdup - duplicate a string
 * @param str - the string
 * @return {char *} - returns a new pointer with the same content as the original
 **/
char * strdup(const char * str);

/**
 * @brief trim - trim whitespace from the beginning and end of a string
 * @param str - the string
 * @return {char *} - returns a part of the string, with leading and trailing whitespace omitted
 **/
char * trim(char * str);

#endif
