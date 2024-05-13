#ifndef TIN_UTILITIES_HASH

typedef unsigned long (*T_HashFunc)(const void *);

unsigned long t_utilities_hash_int(const void *x);

unsigned long t_utilities_hash_string(const void *str);

unsigned long t_utilities_hash_float(const void *x);

#endif