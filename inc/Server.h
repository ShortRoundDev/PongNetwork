#pragma once

#include "Vec2.h"
#include "Types.h"

#ifdef __linux__
#include <pthread.h>
#include <arpa/inet.h>

typedef pthread_t Thread;
#endif

#define SERVER (ServerInstance)

typedef struct PosMessage{
    u8 type;
    Vec2_t pos;
} PosMessage_t;

typedef struct Server {
    int socket;
    Thread receiver;
    Thread transmitter;
    bool clientSet;
    struct sockaddr_in client;
} Server_t;
extern Server_t* ServerInstance;

bool CreateServer();
bool ConnectServer(char* host, int port);
void* TryConnectServer(void* data);

void* ReceiveMessages(void* data);
void* SendMessages(void* data);

void HandleMessages(u8* data, struct sockaddr_in client);
void HandleServerWaitingMessages(u8* data, struct sockaddr_in client);
void HandleServerPlayingMessages(u8* data, struct sockaddr_in client);