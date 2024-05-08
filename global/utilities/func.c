#include "func.h"
#include "stdio.h"

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

// TODO compare/equal/display string
// TODO compare/equal/display float
