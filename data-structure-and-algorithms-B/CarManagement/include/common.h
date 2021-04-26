#pragma once
#ifndef COMMON_H
#define COMMON_H

#include <cstdio>

//////// Common Macros

#define panic()                                                                \
    {                                                                          \
        printf("[ERROR] Panic at %s: %d\n", __FILE__, __LINE__);               \
        exit(-1);                                                              \
    }

#endif // COMMON_H