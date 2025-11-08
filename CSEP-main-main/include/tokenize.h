#ifndef TOKENIZE_H
#define TOKENIZE_H
#include <string.h>
#include <stdlib.h>

#warning "tokenize.h is deprecated. gen_tokenize.h should be used instead."

/* tokenize.h is strictly for presentation. The general tokenize (gen_tokenize.h)
header file should be used in all future cases. */

#define MAX_LENGTH 500

typedef struct {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
} Login;

typedef struct {
    char name[MAX_LENGTH];
    char skill[MAX_LENGTH];
    char request[MAX_LENGTH];
    float trust;
} User;

// Handles our strings using a delimiter of our choice.
static inline void tokenize(User *ptrUsr, char *strToParse, char *delimiter) {
    char* token = strtok(strToParse, delimiter);

    if (token != NULL) {
        strcpy(ptrUsr->name, token);
    }
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(ptrUsr->skill, token);
    }

    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(ptrUsr->request, token);
    }

    token = strtok(NULL, delimiter);
    if (token != NULL) {
        ptrUsr->trust = atof(token);
    }
}

#endif
