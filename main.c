#include <stdio.h>
#include <windows.h>
#include "global/vector/vector.h"

int main()
{
    MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);

    GlobalMemoryStatusEx(&status);
    printf("Total physical memory: %I64d bytes\n", status.ullTotalPhys);
    printf("Available physical memory before allocation: %I64d bytes\n", status.ullAvailPhys);

    // T_Vector vector = t_vector_init(sizeof(int));
    // t_vector_resize(&vector, 10);
    int* number = malloc(sizeof(int));
    // printf("Total memory used by vector: %d bytes\n", t_vector_memory_usage(&vector));

    GlobalMemoryStatusEx(&status);
    printf("Available physical memory after allocation: %I64d bytes\n", status.ullAvailPhys);

    return 0;
}
