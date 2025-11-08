#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/gen_tokenize.h"
#include "../include/io.h"
#include "../include/err.h"

// User Login
int newUser(Login *, int *);
User* loginUser(User *, Login *, int *);
void resolveEmptyField(User *);

// UI
User* loginPage(User *, Login *, int *);
void mainPage(User *, User *, int);

// Skill Requests and Skill Listings
void skillSearch(User *, int);
void skillManage(User *);
void requestManage(User *);
void requestView(User *, int);
void viewMessage(User *);
void sendMessage(User *, User *, int);

// Trust
void rateUser(User *, int);

// ===============
// =Main Function=
// ===============
int main() {
    User *ptrUsr = NULL;
    User *currentUser = NULL;
    Login *ptrLogin = NULL;
    int numOfUsers = 0;

    ptrLogin = loadLoginData(ptrLogin, &numOfUsers);
    ptrUsr = loadUserData(ptrUsr);
    CHECK(ptrLogin);
    CHECK(ptrUsr);

    currentUser = loginPage(ptrUsr, ptrLogin, &numOfUsers);
    if (currentUser) {
        mainPage(currentUser, ptrUsr, numOfUsers);
        dataFullSave(currentUser, ptrUsr, numOfUsers);
    }

    dataAppend(ptrLogin, numOfUsers);

    free(ptrLogin);
    free(ptrUsr);
    free(currentUser);

    return 0;
}

// ======================
// =Registration & Login=
// ======================
int newUser(Login *ptrLogin, int *numOfUsers) {
    char comparisonUser[MAX_LENGTH], comparisonPass[MAX_LENGTH];
    int usr_exist = false;

    printf("Please enter a new Username and Password:\n");
    printf("Username: ");
    scanf("%s", comparisonUser);
    getchar();

    for (int i = 0; i <= *numOfUsers; i++) {
        if (strcmp(comparisonUser, ptrLogin[i].username) == 0) {
            printf("Username already exists.\n");
            usr_exist = true;
            break;
        }
    }

    if (!usr_exist) {
        printf("Password: ");
        scanf("%s", comparisonPass);
        strcpy(ptrLogin[*numOfUsers].username, comparisonUser);
        strcpy(ptrLogin[*numOfUsers].password, comparisonPass);
        getchar();
        return *numOfUsers + 1;
    }

    return *numOfUsers;
}

User* loginUser(User *ptrUsr, Login *ptrLogin, int *numOfUsers) {
    User* currentUser = NULL;
    char comparisonUser[MAX_LENGTH];
    char comparisonPass[MAX_LENGTH];

    printf("Please enter your username and password:\n");
    printf("Username: ");
    scanf("%s", comparisonUser);
    getchar();

    printf("Password: ");
    scanf("%s", comparisonPass);
    getchar();

    for (int i = 0; i <= *numOfUsers; i++) {
        if (strcmp(comparisonUser, ptrLogin[i].username) == 0 &&
            strcmp(comparisonPass, ptrLogin[i].password) == 0)
        {
            printf("%sSuccess!\n", AC_GREEN);
            currentUser = calloc(1, sizeof(User));
            CHECK(currentUser);
            strcpy(currentUser->name, ptrLogin[i].username);
            strcpy(currentUser->skill, ptrUsr[i].skill);
            strcpy(currentUser->request, ptrUsr[i].request);
            strcpy(currentUser->message, ptrUsr[i].message);
            strcpy(currentUser->sender, ptrUsr[i].sender);
            currentUser->hasMessage = ptrUsr[i].hasMessage;
            currentUser->trust = ptrUsr[i].trust;
            resolveEmptyField(currentUser);
            break;
        }
    }

    return currentUser;
}

void resolveEmptyField(User *currentUser) {
    if (currentUser->skill[0] == '\0' && currentUser->request[0] == '\0' &&
        currentUser->trust == 0)
    {
        strcpy(currentUser->skill, "N/A");
        strcpy(currentUser->request, "N/A");
        currentUser->trust = 1;
    }

    else if (currentUser->skill[0] == '\0')
    {
        strcpy(currentUser->skill, "N/A");
    }

    else if (currentUser->request[0] == '\0')
    {
        strcpy(currentUser->request, "N/A");
    }

    else if (currentUser->message[0] == '\0' || currentUser->sender[0] == '\0')
    {
        strcpy(currentUser->message, "N/A");
        strcpy(currentUser->sender, "N/A");
    }
}


// =============
// =UI Features=
// =============

User* loginPage(User *ptrUsr, Login *ptrLogin, int *numOfUsers) {
    User *currentUser = NULL;
    bool login_state = false;
    int option;

    while (login_state != true) { // Keep displaying this page while the user is not logged in.
        printf("%s***** Login Page *****\n", AC_WHITE);
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("**********************\n");
        printf("Choose an option: ");
        scanf("%d", &option);
        getchar();

        switch (option) { // Handles user choices.
            case 1:
                *numOfUsers = newUser(ptrLogin, numOfUsers);
                break;
            case 2:
                currentUser = loginUser(ptrUsr, ptrLogin, numOfUsers); // Setting the return state of the loginUser function
                if (currentUser == NULL) {
                    printf("%sAttempt login again.\n", AC_RED);
                    login_state = false;
                    break;
                }
                login_state = true;
            break;
            case 3:
                return NULL;
            default:
                printf("Invalid option. Please try again.");
                break;
        }
    }
    return currentUser;
}

void mainPage(User *currentUser, User *allUsers, int numOfUsers) {
    while (1) {
        int option = 0;
        printf("%sWelcome %s!\n", AC_WHITE, currentUser->name);
        printf("***** Main Menu *****\n");
        printf("1. Manage My Skills\n");
        printf("2. Manage My Requests\n");
        printf("3. View User Requests\n");
        printf("4. Search Skills\n");
        printf("5. Rate User\n");
        printf("6. Inbox\n");
        printf("7. Send Message\n");
        printf("8. Exit\n");
        printf("*********************\n");
        printf("Choose an option: ");
        scanf("%d", &option);
        getchar();

        switch (option) {
            case 1:
                skillManage(currentUser);
                break;
            case 2:
                requestManage(currentUser);
                break;
            case 3:
                requestView(allUsers, numOfUsers);
                break;
            case 4:
                skillSearch(allUsers, numOfUsers);
                break;
            case 5:
                rateUser(allUsers, numOfUsers);
                break;
            case 6:
                viewMessage(currentUser);
                break;
            case 7:
                sendMessage(currentUser, allUsers, numOfUsers);
                break;
            case 8:
                return;
            default:
                printf("Invalid option. Please try again.");
                break;
        }
    }
}

// ===============
// =Functionality=
// ===============
void skillManage(User* currentUser) {
    char newSkill[MAX_LENGTH];

    printf("Current Skill: %s\n", currentUser->skill);
    printf("Enter New Skill: ");
    fgets(newSkill, MAX_LENGTH, stdin);
    newSkill[strlen(newSkill) - 1] = '\0';
    strcpy(currentUser->skill, newSkill);
    printf("Skill Changed to: %s\n\n", currentUser->skill);
}

void requestManage(User* currentUser) {
    char new_request[MAX_LENGTH];

    printf("Current Request: %s\n", currentUser->request);
    printf("Enter New Request: ");
    fgets(new_request, MAX_LENGTH, stdin);
    new_request[strlen(new_request) - 1] = '\0';
    strcpy(currentUser->request, new_request);
    printf("Request Changed to: %s\n", currentUser->request);
}

void requestView(User* allUsers, int numOfUsers) {
    char request_search[MAX_LENGTH];
    char* substring;
    int minTrust;
    int user_num = 1;
    int found = 0;
   
    User newUsers[MAX_USERS];
    int newCount = 0;

    printf("Enter Request to Search: ");
    fgets(request_search, MAX_LENGTH, stdin);
    request_search[strlen(request_search) - 1] = '\0';

    printf("Enter User's Minimum Trust: ");
    scanf("%d", &minTrust);
    getchar();

    for (int i = 0; i < numOfUsers ; i++) {
        if (allUsers[i].trust >= minTrust) {
        substring = strstr(allUsers[i].request, request_search);
        if (substring != NULL) {
            newUsers[newCount++] = allUsers[i];
        }
    }
    }

    for (int i = 0; i < newCount - 1; i++) {
        for (int j = 0; j < newCount - 1 - i; j++) {
            if (strcmp(newUsers[j].name, newUsers[j + 1].name) > 0) {
                User temp = newUsers[j];
                newUsers[j] = newUsers[j + 1];
                newUsers[j + 1] = temp;
            }
        }
    }

    printf("---------------------------------------------------------------------------------------\n");
    printf("\n%-6s| %-19s| %-33s| %-8s\n", "No.", "Name", "Request", "Trust");
    printf("---------------------------------------------------------------------------------------\n");

    for (int i = 0; i < newCount; i++) {
        printf("%-5d %-20s %-35s %-10.2f\n", user_num, newUsers[i].name, newUsers[i].request, newUsers[i].trust);
        user_num++;
        found = 1;
    }

    if (!found) {
        printf("No user with this request could be found.\n\n");
    }
}

void skillSearch(User* allUsers, int numOfUsers) {
    char skill_search[MAX_LENGTH];
    char* substring;
    int minTrust;
    int user_num = 1;
    int found = 0;
   
    User newUsers[MAX_USERS];
    int newCount = 0;
    printf("Enter Skill to Search: ");
    fgets(skill_search, MAX_LENGTH, stdin);
    skill_search[strlen(skill_search) - 1] = '\0';

    printf("Enter Minimum Trust to Filter (1 - 10): ");
    scanf("%d", &minTrust);
    for (int i = 0; i < numOfUsers ; i++) {
        if (allUsers[i].trust >= minTrust) {
            substring = strstr(allUsers[i].skill, skill_search);
            if (substring != NULL) {
                newUsers[newCount++] = allUsers[i];
            }
        }
    }
    for (int i = 0; i < newCount - 1; i++) {
        for (int j = 0; j < newCount - 1 - i; j++) {
            if (strcmp(newUsers[j].name, newUsers[j + 1].name) > 0) {
                User temp = newUsers[j];
                newUsers[j] = newUsers[j + 1];
                newUsers[j + 1] = temp;
            }
        }
    }
    printf("---------------------------------------------------------------------------------------\n");
    printf("\n%-6s| %-19s| %-23s| %-8s\n", "No.", "Name", "Skill", "Trust");
    printf("---------------------------------------------------------------------------------------\n");
    for (int i = 0; i < newCount; i++) {
        printf("%-5d %-20s %-24s %-10.2f\n", user_num, newUsers[i].name, newUsers[i].skill, newUsers[i].trust);
        user_num++;
        found = 1;
    }

    if (!found) {
        printf("No user with this skill could be found.\n\n");
    }
}

void viewMessage(User *currentUser) {
    printf("\n*****Your Inbox*****\n\n");
    if (currentUser->hasMessage == true)
    {
        printf("%s sent: %s\n\n", currentUser->sender, currentUser->message);
        currentUser->hasMessage = false;
        strcpy(currentUser->message, "N/A");
        strcpy(currentUser->sender, "N/A");
        printf("********************\n\n");
        return;
    }

    printf("Nothing new here...\n\n");
    strcpy(currentUser->message, "N/A");
    strcpy(currentUser->sender, "N/A");

    printf("********************\n\n");
}

void sendMessage(User *currentUser, User *allUsers, int numOfUsers){
    char target[MAX_LENGTH];
    char string[MAX_LENGTH];

    printf("Send message to: ");
    fgets(target, sizeof(target), stdin);
    target[strcspn(target, "\n")] = 0;

    printf("Enter your message: ");
    fgets(string, sizeof(string), stdin);
    string[strlen(string) - 1] = '\0';

    for (int i = 0; i < numOfUsers; i++)
    {
        if (strcmp(allUsers[i].name, target) == 0)
        {
            strcpy(allUsers[i].message, string);
            strcpy(allUsers[i].sender, currentUser->name);
            allUsers[i].hasMessage = true;
            break;
        }
    }
}

void rateUser(User *allUsers, int numOfUsers) {
    char userToFind[MAX_LENGTH];
    float rating;
    float temp;

    // Enter user to search for
    printf("Which user would you like to rate?: ");
    fgets(userToFind, sizeof(userToFind), stdin);
    userToFind[strcspn(userToFind, "\n")] = 0;
    printf("How do you think they did? (1 - 10): ");
    scanf("%f", &rating);
    getchar();

    if (rating <= 0 || rating > 10) {
        LOG(ERR_INVALID_INPUT, "Please enter a rating from 1 - 10\n");
        return;
    }

    // Search users with that name
    int i = 0;
    for (; i < numOfUsers; i++) {
        if (strcmp(allUsers[i].name, userToFind) == 0) {
            temp = allUsers[i].trust;
            allUsers[i].trust = (allUsers[i].trust + rating) / 2;
            break;
        }
    }

    if (allUsers[i].trust < 0 || allUsers[i].trust > 10) {
        LOG(ERR_CORRUPT_DATA, "Invalid trust score was created. Resetting to previous...\n");
        allUsers[i].trust = temp;
    }

    return;
}
