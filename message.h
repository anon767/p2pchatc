//
// Created by Tom on 06.05.2017.
//

#ifndef P2PCHATC_MESSAGE_H
#define P2PCHATC_MESSAGE_H
#define MESSAGESIZE 256
#define HASHSIZE 5 //5 chars
#define DELIMITER "|"
#define DELIMITERCHAR '|'
typedef struct packet_t {
    char body[MESSAGESIZE];
    char *hash;
    char *senderHash;
} message;

char *prependString(char *stringa, char *stringb);

char **str_split(const char *a_str, const char a_delim);

char *gen_random();

#endif //P2PCHATC_MESSAGE_H
