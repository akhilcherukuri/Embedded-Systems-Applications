#include "midproblemtwo.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool extract_string_between(const char *source, char *output_string, char between) {
  // char line[256];
  // strcpy(line, source);
  //   output_string = strtok(line, between);
  //   output_string = strtok(NULL, between);
  if (source == NULL) {
    return false;
  }

  int len = strlen(source);
  int startpt, endpt;
  for (int i = 0; i < len; i++) {
    if (source[i] == between) {
      startpt = i;
      break;
    }
  }
  for (int i = i + 1; i < len; i++) {
    if (source[i] == between) {
      endpt = i;
      break;
    }
  }
  int final_length = startpt - endpt - 1;
  for (int i = 0; i < final_length; i++) {
    output_string[i] = source[startpt + i + 1];
  }
  return true;
}
