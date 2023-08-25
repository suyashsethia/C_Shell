#ifndef _SEEK_H_
#define _SEEK_H_
#include <stdbool.h>
void seek(
    int i,
    char *target,
    int f,
    int e,
    int d,
    
    char *tofind);


void travel_recursive(char *tofind,
                      char *target,
                      char *current_path,
                      char **results,
                      int f,
                      int d,
                      int *result_count);
#endif