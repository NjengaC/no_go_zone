#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

int _printf(const char *format, ...);
char *Itoa(int n);
char *bin_convert(unsigned long int n);
#endif

