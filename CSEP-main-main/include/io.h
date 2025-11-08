#ifndef IO_H
#define IO_H
#include <stdbool.h>

#define MAX_LENGTH 120
#define MAX_USERS 1000

typedef struct {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
} Login;

typedef struct {
    char name[MAX_LENGTH];
    char skill[MAX_LENGTH];
    char request[MAX_LENGTH];
    char message[MAX_LENGTH];
    char sender[MAX_LENGTH];
    bool hasMessage;        // Flag for whether user has a message or not
    float trust;            // User reputation
} User;

extern Login* loadLoginData(Login *ptrLogin, int *numOfUsers);
extern User* loadUserData(User *ptrUsr);
extern void dataAppend(Login *ptrLogin, int numOfUsers);
extern void dataFullSave(User* currentUser, User *ptrUsr, int numOfUsers);

#endif
