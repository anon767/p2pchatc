//
// Created by Tom on 06.05.2017.
//

#ifndef P2PCHATC_MESSAGE_H
#define P2PCHATC_MESSAGE_H
typedef struct packet_t {
    char * body[5000];
    char * senderHash;
} message;

#endif //P2PCHATC_MESSAGE_H
