//
// Created by Tom on 06.05.2017.
//

#ifndef P2PCHATC_PEER_H
#define P2PCHATC_PEER_H
#include <stdio.h>
#ifdef __linux__
#include <sys/socket.h>
#elif _WIN32

#include <Windows.h>

#pragma comment(lib, "ws2_32.lib")
#endif
typedef struct peer {
    boolean valid;
    char *hash;
    int port;
    struct sockaddr_in addr;
    struct peer * next;
} peer;
boolean hashExists(peer *peers, char *hash);
boolean checkSockaddr(struct sockaddr_in a, struct sockaddr_in b);
boolean addrExists(peer *peers, struct sockaddr_in *b);
void addToTail(peer *peers, peer *peer);



#endif //P2PCHATC_PEER_H
