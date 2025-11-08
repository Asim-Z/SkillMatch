#include "../include/gen_tokenize.h"
#include "../include/err.h"
#include "../include/io.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LENGTH 120

// ==============
// =Data Loading=
// ==============

/* This data function actually handles moving login information from our files to our structs.
 * @param ptrLogin Array of login information.
 * @param numOfUsers Pointer to the number of users in the file.
 */
Login* loadLoginData(Login *ptrLogin, int *numOfUsers) {
    FILE* file = fopen("../userData/login_info.txt", "r");
    if (!file) {
        LOG(ERR_FILE_OPEN, "Could not open login info.");
        return NULL;
    }
    int capacity = 5;

    ptrLogin = (Login *)calloc(capacity, sizeof(Login));
    CHECK(ptrLogin);


    while (fscanf(file, "%s %s\n", ptrLogin[*numOfUsers].username, ptrLogin[*numOfUsers].password) != EOF) {
        (*numOfUsers)++;
        if (*numOfUsers >= capacity) {
            capacity *= 2;
            Login* temp = (Login *)realloc(ptrLogin, capacity * sizeof(Login));
            CHECK(temp);
            ptrLogin = temp;
        }
    }

    if (!numOfUsers) {
        LOG(ERR_NO_USERS, "No users exist.");
    }

    fclose(file);

    return ptrLogin;
}

/* This data function presents a problem with reading data from a file
 * or even reading strings in general. How can I properly separate information?
 * @param ptrUsr Array of user information.
 */
User* loadUserData(User *ptrUsr) {
    FILE* file = fopen("../userData/profile_info.txt", "r");
    if (!file) {
        LOG(ERR_FILE_OPEN, "Could not open profile info.");
        return NULL;
    }
    char string[MAX_LENGTH];
    int capacity = 5;

    ptrUsr = (User *)calloc(capacity, sizeof(User));

    int i = 0;
    // Read each line as one whole string
    while (fgets(string, MAX_LENGTH, file)) {
        if (i >= capacity) {
            capacity *= 2;
            User *temp = (User *)realloc(ptrUsr, capacity * sizeof(User));
            CHECK(temp);
            ptrUsr = temp;
        }

        // This array of structs is specifically for tokenize() (You can ignore it)
        Fields field[] =
        {
            {ptrUsr[i].name, STRING, sizeof(ptrUsr[i].name)},
            {ptrUsr[i].skill, STRING, sizeof(ptrUsr[i].skill)},
            {ptrUsr[i].request, STRING, sizeof(ptrUsr[i].request)},
            {ptrUsr[i].message, STRING, sizeof(ptrUsr[i].message)},
            {ptrUsr[i].sender, STRING, sizeof(ptrUsr[i].sender)},
            {&ptrUsr[i].hasMessage, BOOL, sizeof(ptrUsr[i].hasMessage)},
            {&ptrUsr[i].trust, FLOAT, sizeof(ptrUsr[i].trust)}
        };

        // TODO: Fix tokenize to handle double delimiter case ("||")
        tokenize(string, "|", field, 7); // Here the string will be split using a delimiter
        if (ptrUsr[i].trust <= 0 ||ptrUsr[i].trust > 10)
        {
            LOG(ERR_CORRUPT_DATA, "Check data formatting in profile_info.txt on line %d.", i + 1);
            exit(EXIT_FAILURE);
        }

        i++;
    }

    fclose(file);

    return ptrUsr;
}

// =========================
// =Data Appends & Rewrites=
// =========================
int userExists(User* currentUser, User* ptrUsr, int numOfUsers) {
    int location = 0;

    for (int i = 0; i < numOfUsers; i++) {
        if (strcmp(currentUser->name, ptrUsr[i].name) == 0)
        {
            return location;
        }

        location++;
    }

    return -1;
}

// Useful for not having to type this out all the time
void printUserToFile(User* ptrUsr, FILE* file) {
    fprintf(file, "%s|%s|%s|%s|%s|%d|%.2f\n", ptrUsr->name, ptrUsr->skill,
            ptrUsr->request, ptrUsr->message, ptrUsr->sender, ptrUsr->hasMessage,
            ptrUsr->trust);
}

void dataAppend(Login *ptrLogin, int numOfUsers) {
    FILE* file = fopen("../userData/login_info.txt", "a+");
    if (!file) {
        LOG(ERR_FILE_OPEN, "Could not open login info.");
        return;
    }
    char comparisonUser[MAX_LENGTH], comparisonPass[MAX_LENGTH];
    bool exists = false;

    rewind(file);
    while (fscanf(file, "%s %s", comparisonUser, comparisonPass) != EOF) {
        if (strcmp(comparisonUser, ptrLogin[numOfUsers - 1].username) == 0 &&
            strcmp(comparisonPass, ptrLogin[numOfUsers - 1].password) == 0) {
            exists = true;
            break;
        }
    }

    if (!exists) {
        fseek(file, 0, SEEK_END - 1);
        fprintf(file, "%s %s\n", ptrLogin[numOfUsers - 1].username, ptrLogin[numOfUsers - 1].password);
    }

    fclose(file);
    return;
}

void dataFullSave(User* currentUser, User *ptrUsr, int numOfUsers) {
    FILE* file = fopen("../userData/profile_info.txt", "w");
    if (!file)
    {
        LOG(ERR_FILE_OPEN, "Could not open profile info.");
        return;
    }

    int exists = userExists(currentUser, ptrUsr, numOfUsers);

    if (exists == -1)
    {
        ptrUsr[numOfUsers - 1] = *currentUser;
    }

    else
    {
        ptrUsr[exists] = *currentUser;
    }

    for (int i = 0; i < numOfUsers; i++)
    {
        printUserToFile(&ptrUsr[i], file);
    }

    fclose(file);
}


