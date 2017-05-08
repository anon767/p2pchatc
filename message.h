//
// Created by Tom on 06.05.2017.
//

#ifndef P2PCHATC_MESSAGE_H
#define P2PCHATC_MESSAGE_H
#define MESSAGESIZE 256
#define HASHSIZE 5 //5 chars
#define DELIMITER "|"
typedef struct packet_t {
    char body[MESSAGESIZE];
    char *senderHash;
} message;

char *prependString(char *stringa, char *stringb);

#endif //P2PCHATC_MESSAGE_H
