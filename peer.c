//
// Created by Tom on 06.05.2017.
//

#include "peer.h"


boolean hashExists(peer *peers, char *hash) {
    peer *current = peers;
    while (current->next) {
        if (strcmp(current->next->hash, hash)) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

boolean checkSockaddr(struct sockaddr_in a, struct sockaddr_in b) {
    return a.sin_addr.S_un.S_addr == b.sin_addr.S_un.S_addr;
}

boolean addrExists(peer *peers, struct sockaddr_in *b) {
    peer *current = peers;
    while (current->next != NULL) {
        if (checkSockaddr(current->next->addr, *b)) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void addToTail(peer *peers, peer *peer) {
    struct peer *current = peers;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = peer;
}
