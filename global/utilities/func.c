#include "func.h"
#include "stdio.h"
#include "string.h"

bool t_utilities_compareInt(const void *x1, const void *x2)
{
    return *(int *)x1 > *(int *)x2;
}
bool t_utilities_equalInt(const void *x1, const void *x2)
{
    return *(int *)x1 == *(int *)x2;
}

const void t_utilities_display_int(const void *element)
{
    printf("%d ", *(int *)element);
}

const void t_utilities_display_String(const void *element) {
    printf("%s ", *(char **)element);
}

bool t_utilities_compareString(const void *x1, const void *x2)
{
    return strcmp((char *)x1, (char *)x2);
}
bool t_utilities_equalString(const void *x1, const void *x2)
{
    return strcmp((const char *)x1, (const char *)x2) == 0;
}
// TODO compare/equal/display float
