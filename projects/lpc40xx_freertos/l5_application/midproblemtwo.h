/**
 * Extract a group of characters between a character
 *
 * Assumption:
 * - output_string is memory pointer that is at least the size of strlen(source)
 *
 * Behavior:
 * - If 'between' char does not appear at least twice, return false
 * - Given *source="hello 'world' 123", and between=' then *output_string should be set to "world"
 *
 * Another example:
 * - *source = "value = 'one two three'"
 * - between = ' (single quote)
 * - *output_string should be set to "one two three"
 *
 * @param source Input string, such as 'hello .123. world'
 * @param output_string The output string is written here
 * @param between The character between which we should extract a string
 *
 * @returns true if a string has been extracted correctly
 */
#pragma once

#include <stdbool.h>

bool extract_string_between(const char *source, char *output_string, char between);