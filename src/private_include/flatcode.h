#ifndef FLATCODE_H
#define FLATCODE_H

#include <color.h>

typedef enum{
    SUCCESS,
    TRY_FREE_NULL_POINTER,
}FlatCode;

#define CRASH_ON_ERROR(msg, ...) do {                                       \
    fprintf(stderr, BOLD BR_RED "Error" RESET ": " CYAN "%s" RESET " -> "msg,\
            __func__, ##__VA_ARGS__);                                    \
    exit(EXIT_FAILURE);                                                     \
} while (0)


#endif // FLATCODE_ERRORS_H