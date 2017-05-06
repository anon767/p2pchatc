#include <pthread.h>
#include <stdio.h>

#ifdef __linux__
#include <sys/socket.h>
#elif _WIN32

#include <Windows.h>

#pragma comment(lib, "ws2_32.lib")
#endif

#include <pthread.h>
#include <semaphore.h>
#include <ws2tcpip.h>
#include "message.h"
#include "peer.h"

pthread_mutex_t stdout_lock;
pthread_mutex_t peer_list_lock;
peer *self;
int sock;
WSADATA data;

char *gen_random(const int len) {
    char *s = malloc(sizeof(char) * len);
    static const char alphanum[] =
            "0123456789"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
    return s;
}

void setupSocket() {
    self = malloc(sizeof(peer));
    self->valid = 1;
    if (INVALID_SOCKET == (sock = socket(AF_INET, SOCK_DGRAM, 0)) || sock < 0) {
        fprintf(stderr, "%s\n", "error - error creating socket.");
        abort();
    }
    self->hash = gen_random(5);
    self->next = NULL;
    self->addr.sin_family = AF_INET;
    self->addr.sin_addr.s_addr = htonl(INADDR_ANY);
    self->port = 5555;
    self->addr.sin_port = htons(self->port);
    if (bind(sock, (struct sockaddr *) &(self->addr), sizeof(self->addr))) {
        fprintf(stderr, "%s\n", "error - error binding.");
        abort();
    }
}


void receive_packet() {

    peer *sender = malloc(sizeof(peer));

    socklen_t addrlen = 10;
    message *pkt = malloc(sizeof(message));
    int status;
    while (1) {
        struct sockaddr_storage src_addr;
        socklen_t src_addr_len = sizeof(src_addr);
        ssize_t count = recvfrom(sock, &pkt->body, sizeof(pkt->body), 0, (struct sockaddr *) &src_addr, &src_addr_len);
        if (!addrExists(self, (struct sockaddr_in *) &src_addr)) {
            peer *p = malloc(sizeof(peer));
            p->addr = *(struct sockaddr_in *) &src_addr;
            p->hash = gen_random(5);
            addToTail(self, p);
            printf("added peer %s\r\n", p->hash);
        }
        if (count == -1) {
            printf("%s", strerror(errno));
        } else if (count == sizeof(pkt->body)) {
            printf("datagram too large for buffer: truncated");
        } else {
            printf("%s\r\n", pkt->body);
        }

    }
}

int main() {
    WSAStartup(MAKEWORD(2, 2), &data);
    setupSocket();
    receive_packet();
    WSACleanup();
    return 0;
}