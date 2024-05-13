#ifndef TIN_UTILITIES_FUNC
#include <stdbool.h>

typedef const void (*T_DisplayFunc)(const void *);
typedef bool (*T_CompareFunc)(const void *, const void *);
typedef bool (*T_EqualFunc)(const void *, const void *);

bool t_utilities_compareInt(const void *x1, const void *x2);
bool t_utilities_equalInt(const void *x1, const void *x2);
const void t_utilities_display_int(const void *element);
bool t_utilities_compareString(const void *x1, const void *x2);
bool t_utilities_equalString(const void *x1, const void *x2);
const void t_utilities_display_String(const void *element);
#endif