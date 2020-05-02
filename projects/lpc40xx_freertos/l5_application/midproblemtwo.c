#include "midproblemtwo.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool extract_string_between(const char *source, char *output_string, char between) {
char line[];
strcpy(line, source);
  output_string = strtok(line, between);
  output_string = strtok(NULL, between);
// output_string = line.Remove(line.IndexOf(')')).Substring(source.IndexOf('(') + 1);



}
