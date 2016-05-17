#ifndef __UTILS_H_INCLUDED__
#define __UTILS_H_INCLUDED__

#include <sys/time.h>

void constrain(double min, double max, double *value);
long get_time();

#endif