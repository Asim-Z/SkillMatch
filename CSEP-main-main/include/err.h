#ifndef ERR_H
#define ERR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef enum {
    ERR_NONE = 0,
    ERR_FILE_OPEN,
    ERR_MEMORY_ALLOC,
    ERR_INVALID_INPUT,
    ERR_USER_NOT_FOUND,
    ERR_NO_USERS,
    ERR_CORRUPT_DATA,
    ERR_NULL,
    ERR_DUPLICATE_USER,
    ERR_ORPHANED_USER
} ErrorID;

// Error handling to help with some basic debugging
// Todo: Implement ERR_NO_USERS, ERR_USER_NOT_FOUND, ERR_NULL,
// ERR_DUPLICATE_USER, ERR_ORPHANED_USER
static void log(ErrorID id, int line, const char* file, const char* err_message, ...) {
    va_list args;
    va_start(args, err_message);

    const char* typeError[] = {
        "No error was found",
        "File operation failed",
        "Memory allocation failed",
        "Invalid input was attempted",
        "User was not found",
        "There are no users recorded",
        "Malformed data or unexpected format"
    };

    fprintf(stderr, "ERROR! %s : %d | Code : %d => ", typeError[id], line, id);
    vfprintf(stderr, err_message, args);
    fprintf(stderr, "\n");

    va_end(args);
}

#define LOG(id, ...) log(id, __LINE__, __FILE__, __VA_ARGS__)


/* Simple memory check just to avoid writing this out every time we allocate memory.
 * Terminates program upon failure.
 * @param ptrStruct Array of structs you wish to check.
 */
static inline void memcheck(void* ptrStruct, const char* file, int line) {
    if (!ptrStruct) {
        LOG(ERR_NULL, "Memory could not be allocated to pointer.");
        exit(EXIT_FAILURE);
    }
}

#define CHECK(ptrStruct) memcheck(ptrStruct, __FILE__, __LINE__)

#endif
