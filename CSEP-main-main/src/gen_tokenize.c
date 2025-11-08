#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/gen_tokenize.h"

/* This function chunks information using a delimiter (which you can choose).
 * It should be noted that at this stage there is virtually no error handling, so be careful.
 * @param strToParse String that contains a delimiter.
 * @param delimiter Break point for each chunk of information.
 * @param field Array of what information is stored in a struct.
 * @param sizeField Number of datatypes that are stored in a struct.
 */
void tokenize(char *strToParse, char *delimiter, Fields field[], int sizeField) {
    char *token = strtok(strToParse, delimiter);

    int i = 0;
    while (i < sizeField && token != NULL) {
        if (!field[i].field) break;

        if (field[i].type == STRING) {
            strncpy((char *)field[i].field, token, field[i].size - 1);
            ((char *)field[i].field)[field[i].size - 1] = '\0'; // We set the null character at the end of the string
        }

        else if (field[i].type == INT) {
            *(int *)field[i].field = atoi(token);
        }

        else if (field[i].type == FLOAT) {
            *(float *)field[i].field = atof(token);
        }

        else if (field[i].type == BOOL) {
            *(bool *)field[i].field = atoi(token) ? true : false;
        }

        token = strtok(NULL, delimiter);
        i++;
    }
}
