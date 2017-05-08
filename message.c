//
// Created by Tom on 08.05.2017.
//
#include <malloc.h>
#include <mem.h>
#include "message.h"

const char *delimiter = DELIMITER;

/*
 * Split by delimiter
 */
char *prependString(char *stringa, char *stringb) {
    const unsigned int RESULT_SIZE = strlen(stringa) + strlen(delimiter) + strlen(stringb) + 3 * sizeof('\0');
    char *result = malloc(RESULT_SIZE);
    strcpy(result, stringa);
    strcat(result, delimiter);
    strcat(result, stringb);
    strcat(result,(char*)"\0");
    return result;
}

