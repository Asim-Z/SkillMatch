#ifndef GEN_TOKENIZE_H
#define GEN_TOKENIZE_H

#include <stdlib.h>
#include <stdio.h>

#define AC_BLACK "\x1b[30m"
#define AC_RED "\x1b[31m"
#define AC_GREEN "\x1b[32m"
#define AC_YELLOW "\x1b[33m"
#define AC_BLUE "\x1b[34m"
#define AC_MAGENTA "\x1b[35m"
#define AC_CYAN "\x1b[36m"
#define AC_WHITE "\x1b[37m"
#define AC_NORMAL "\x1b[m"

typedef enum {STRING, INT, FLOAT, DOUBLE, BOOL} Type;

typedef struct {
    void *field;
    Type type;
    size_t size;
} Fields;

extern void tokenize(char *strToParse, char *delimiter, Fields field[], int sizeField);

#endif
