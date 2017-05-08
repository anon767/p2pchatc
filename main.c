#include <pthread.h>
#include <stdio.h>

#ifdef __linux__
#include <sys/socket.h>

#elif _WIN32

#include <Windows.h>

#pragma comment(lib, "ws2_32.lib")
#endif

#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <ws2tcpip.h>
#include "message.h"
#include "peer.h"


#define DEFAULTSERVERPORT 5555
boolean running;
HANDLE receiveThread;
peer *self;
int sock;
WSADATA data;

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

void setupSocket() {
    self = malloc(sizeof(peer));
    self->valid = 1;
    if (INVALID_SOCKET == (sock = socket(AF_INET, SOCK_DGRAM, 0)) || sock < 0) {
        fprintf(stderr, "%s\n", "error - error creating socket.");
        abort();
    }
    self->hash = gen_random();
    self->next = NULL;
    self->addr.sin_family = AF_INET;
    self->addr.sin_addr.s_addr = htonl(INADDR_ANY);
    self->port = DEFAULTSERVERPORT;
    self->addr.sin_port = htons(self->port);
    if (bind(sock, (struct sockaddr *) &(self->addr), sizeof(self->addr))) {
        fprintf(stderr, "%s\n", "error - error binding.");
        abort();
    }
}


void receive_packet() {

    peer *sender = malloc(sizeof(peer));

    socklen_t addrlen = 10;

    int status;
    while (1) {
        message *pkt = (message *) malloc(sizeof(message));
        struct sockaddr_storage src_addr;
        socklen_t src_addr_len = sizeof(src_addr);
        ssize_t count = recvfrom(sock, pkt->body, sizeof(pkt->body), 0, (struct sockaddr *) &src_addr, &src_addr_len);
        if (!addrExists(self, (struct sockaddr_in *) &src_addr)) {
            peer *p = malloc(sizeof(peer));
            p->addr = *(struct sockaddr_in *) &src_addr;
            p->valid = 1;
            p->hash = gen_random(); //just initial fill
            p->next = NULL;
            addToTail(self, p);
            fprintf(stdout, "added peer %s\r\n", p->hash);
            free(&p);
        }
        if (count == -1) {
            fprintf(stdout, "%s", strerror(errno));
        } else if (count == sizeof(pkt->body)) {
            fprintf(stdout, "datagram too large for buffer: truncated");
        } else {
            fprintf(stdout, "%s\n", pkt->body);
        }
        free(&pkt);
    }
}

void sendToIP(char *ip, const char *content) {
    struct sockaddr_in si_other;
    int s;
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(DEFAULTSERVERPORT);
    si_other.sin_addr.S_un.S_addr = inet_addr(ip);
    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR) {
        fprintf(stdout, "socket() failed with error code : %d \r\n", WSAGetLastError());
    }
    if (sendto(s, content, strlen(content), 0, (struct sockaddr *) &si_other, sizeof(si_other)) == SOCKET_ERROR) {
        fprintf(stdout, "sendto() failed with error code : %d \r\n", WSAGetLastError());
    }
}

void sendToPeers(peer *peers, const char *content) {
    peer *current = peers;
    while (current != NULL) {
        char *contentWithHash = prependString(self->hash, content);
        char *ip = inet_ntoa(current->addr.sin_addr);
        fprintf(stdout, "propagating to %s Hash: %s \r\n", ip, current->hash);
        sendToIP(ip, contentWithHash);
        current = current->next;
        free(&ip);
        free(&contentWithHash);
    }
}

void scan() {

    while (running) {
        char *input = (char *) malloc(sizeof(char) * MESSAGESIZE);
        fgets(input, MESSAGESIZE, stdin);
        sendToPeers(self->next, input);
        free(&input);
    }

}

int main() {
    WSAStartup(MAKEWORD(2, 2), &data);
    setupSocket();
    running = 1;
    receiveThread = CreateThread(NULL, 0, receive_packet, NULL, 0, NULL);
    if (receiveThread) {
        fprintf(stdout, "Listening now\r\n");
    }
    scan();
    WSACleanup();
    return 0;
}