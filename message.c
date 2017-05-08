//
// Created by Tom on 08.05.2017.
//
#include <malloc.h>
#include <mem.h>
#include <assert.h>
#include <time.h>
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
    strcat(result, (char *) "\0");
    return result;
}

char **str_split(const char *a_str, const char a_delim) {
    char **result = 0;
    size_t count = 0;
    char *tmp;
    tmp = malloc(sizeof(char) * strlen(a_str));
    strcpy(tmp, a_str);
    char *tmp2;
    tmp2 = malloc(sizeof(char) * strlen(a_str));
    strcpy(tmp2, a_str);
    char *last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;
    while (*tmp) {
        if (a_delim == *tmp) {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }
    count += last_comma < (tmp2 + strlen(tmp2) - 1);

    count++;

    result = malloc(sizeof(char *) * count);
    if (result) {
        size_t idx = 0;
        char *token = strtok(tmp2, delim);

        while (token) {
           // assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        //assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

char *gen_random() {
    int len = HASHSIZE;
    char *s = malloc(sizeof(char) * len);
    static const char alphanum[] =
            "0123456789"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "abcdefghijklmnopqrstuvwxyz";

    srand(time(NULL));
    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    s[len] = 0;
    return s;
}