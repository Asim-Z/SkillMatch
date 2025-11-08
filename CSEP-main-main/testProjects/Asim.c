#include <stdio.h>
#include <string.h>
#include <stdbool.h>

   #define MAX_LENGTH 100
   #define MAX_USERS 1000
    typedef struct {
    char name[MAX_LENGTH];
    char skill[MAX_LENGTH];
    char request[MAX_LENGTH];
    float trust;
} User;
int main() {
User me = {"asim75062", "Math", "Coding", 5.00};
User users[MAX_USERS] ={
        {"hedge78!4", "Photography", "Photography", 5.80},
        {"quilt@08@", "FitnessWeb_Development", "Photography", 7.10},
        {"igloo5**1", "Graphic_Design", "Podcasting", 5.40},
        {"daisy4*07", "Cloud_Computing", "Video_Editing" ,9.70},
        {"happy87*2", "DevOps", "Filmmaking", 8.30},
        {"tulip0*66", "Gardening", "Storyboarding", 7.50},
        {"yummy966@", "Embedded_Systems", "DevOps", 8.50},
        {"zebra123!", "Machine_Learning", "Data_Science", 6.20},
        {"crisp3!67", "3D_Modeling", "AI_Ethics", 9.80},
        {"waltz44@4", "Writing", "Quantum_Computing", 9.10}
    };

char new_skill[MAX_LENGTH];
char new_request[MAX_LENGTH];
char request_search[MAX_LENGTH];
char skill_search[MAX_LENGTH];
int user_count = 10;

    while (1){
        int option;
        printf("***** Main Menu *****\n");
        printf("1. Manage My Skills\n");
        printf("2. Manage My Requests\n");
        printf("3. View User Requests\n");
        printf("4. Search Skills\n");
        printf("5. Exit\n");
        printf("*********************\n");
        printf("Choose an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Current Skill: %s\n", me.skill);
                printf("Enter New Skill (Replace Space with _) : ");
                scanf("%s", new_skill);
                strcpy(me.skill, new_skill);
                printf("Skill Changed to: %s\n\n", me.skill);

                break;
            case 2:
                printf("Current Request: %s\n", me.skill);
                printf("Enter New Request (Replace Space with _) : ");
                scanf("%s", new_request);
                strcpy(me.request, new_request);
                printf("Request Changed to: %s\n\n", me.request);
                break;
            case 3:
                printf("Enter Request to Search: \n");
                scanf("%s", request_search);
                for (int i=0; i<user_count; i++){
                    if (strcmp(users[i].request, request_search)==0){
                        printf("\nUser: %s\n Skill: %s\n Request: %s\n Trust: %.2f\n\n", users[i].name, users[i].skill, users[i].request, users[i].trust);
                    }
                }
                break;
            case 4:
                printf("Enter Skill to Search: \n");
                scanf("%s", skill_search);
                for (int i=0; i<user_count; i++){
                    if (strcmp(users[i].skill, skill_search)==0){
                        printf("\nUser: %s\n Skill: %s\n Request: %s\n Trust: %.2f\n\n", users[i].name, users[i].skill, users[i].request, users[i].trust);
                    }
                }
                break;
            case 5:
                printf("Exiting..\n");
                break;
            default:
                printf("Incorrect, Try again\n");
        }
}

    return 0;
}
