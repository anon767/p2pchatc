//
// Created by Tom on 06.05.2017.
//

#ifndef P2PCHATC_MESSAGE_H
#define P2PCHATC_MESSAGE_H
#define MESSAGESIZE 2014
typedef struct packet_t {
    char body[MESSAGESIZE];
    char * senderHash;
} message;

#endif //P2PCHATC_MESSAGE_H
