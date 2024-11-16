#ifndef RANDOMBYTES_H____
#define RANDOMBYTES_H____

#include "haslibrandombytes.h"
#ifdef HASLIBRANDOMBYTES
#include <randombytes.h>
#else
extern void randombytes(void *, long long);
extern const char *randombytes_source(void);
#endif

#endif
