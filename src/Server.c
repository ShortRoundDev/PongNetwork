#include "Server.h"
#include "Log.h"
#include "Game.h"
#include "Time.h"
#include "System.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>

Server_t* ServerInstance = null;

bool CreateServer(){
    ServerInstance = malloc(sizeof(Server_t));

    struct sockaddr_in server_addr, client_addr;

    int client_struct_length = sizeof(client_addr);
    ServerInstance->socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if(ServerInstance->socket < 0){
        LOG->err("Error while creating socket");
        return false;
    }
    LOG->info("Successfully created socket");
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(ServerInstance->socket, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0){
        LOG->err("Couldn't bind to port!");
        return -1;
    }

    LOG->info("Done with binding");

    pthread_t thread;
    pthread_create(&thread, NULL, ReceiveMessages, NULL);
    ServerInstance->receiver = thread;

    pthread_t sendThread;
    pthread_create(&sendThread, NULL, SendMessages, NULL);
    ServerInstance->transmitter = sendThread;

    return true;
}

bool ConnectServer(char* host, int port){
    ServerInstance = malloc(sizeof(Server_t));
    
    struct sockaddr_in serverAddr;
    SERVER->socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(SERVER->socket < 0){
        LOG->err("Error while creating socket!");
        return false;
    }
    LOG->info("Successfully created socket");
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(host);
    
    u8 buff = 0xff;

    SERVER->client = serverAddr;
    
    struct sockaddr_in* pthreadMsg = malloc(sizeof(struct sockaddr_in));
    memcpy(pthreadMsg, &serverAddr, sizeof(struct sockaddr_in));

    pthread_t connectThread;
    pthread_create(&connectThread, NULL, TryConnectServer, pthreadMsg);
    
    return true;
}

void* TryConnectServer(void* data){
    struct sockaddr_in serverAddr = *((struct sockaddr_in*)data);
    u8 buff = 0xff;
    while(true){
        if(sendto(SERVER->socket, &buff, sizeof(buff), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) > 0){
            LOG->info("Connected!");
            pthread_t receiveThread;
            pthread_create(&receiveThread, NULL, ReceiveMessages, NULL);
            SERVER->receiver = receiveThread;

            pthread_t sendThread;
            pthread_create(&sendThread, NULL, SendMessages, NULL);
            SERVER->transmitter = sendThread;
            free(data);
            return null;
        }
        usleep(1000000);
    }
}

void* ReceiveMessages(void* data){
    u8 clientMsg[100];
    struct sockaddr_in clientAddr;
    u32 clientStructLength = (u32)sizeof(clientAddr);

    while(true){
        if(
            recvfrom(SERVER->socket, clientMsg, sizeof(clientMsg), 0,
                (struct sockaddr*)&clientAddr, &clientStructLength) < 0
        ){
            LOG->err("Couldn't receive message!");
            continue;
        }

        if(!SERVER->clientSet){
            SERVER->client = clientAddr;
            SERVER->clientSet = true;
        }
        HandleMessages(clientMsg, clientAddr);
        memset(clientMsg, 0, sizeof(clientMsg));
    }
}

void HandleMessages(u8* data, struct sockaddr_in client){
    switch(GAME->state){
        case SERVER_PLAYING:
        case CLIENT_PLAYING:
            HandleServerPlayingMessages(data, client);
            break;
        case SERVER_WAITING:
        case CLIENT_NO_CONNECTION:
            HandleServerWaitingMessages(data, client);
            break;
    }
}

void HandleServerWaitingMessages(u8* data, struct sockaddr_in client){
    if(data[0] == 0xff){
        u8 buff = 0xff;
        if(SYS->isServer){
            sendto(SERVER->socket, &buff, sizeof(buff), 0, (struct sockaddr*)&client, sizeof(client));
            LOG->info("Got connection from client!");
            GAME->state = SERVER_PLAYING;
        } else {
            LOG->info("Got connection to server!");
            GAME->state = CLIENT_PLAYING;
        }
    }
}

void HandleServerPlayingMessages(u8* data, struct sockaddr_in client){
    u32* _buff = (u32*)data;
    u32 total = _buff[0];
    PosMessage_t* messageBuffer = (PosMessage_t*)(_buff + 1);
    for(int i = 0; i < total; i++){
        u8 type = messageBuffer[i].type;
        Vec2_t pos = messageBuffer[i].pos;

        for(int j = 0; j < GAME->totalEntities; j++){
            Entity_t* ent = GAME->entities[j];
            u8 entType = ent->type;
            if(type == entType){
                ent->setPos(ent, pos);
                break;
            }
        }
    }
}

void* SendMessages(void* data){
    u8 buff[100];
    while(true){
        usleep(100000);
        if(!SERVER->clientSet){
            LOG->warn("Client not connected... sleeping...");
            continue;
        }
        memset(buff, 0, sizeof(buff));
        u8* _buff = buff + sizeof(u32);
        PosMessage_t* messageBuffer = (PosMessage_t*)_buff;

        int outEnts = 0;
        for(int i = 0; i < GAME->totalEntities; i++){
            Entity_t* ent = GAME->entities[i];
            if(ent->serialized && ent->serialize != null){
                ent->serialize(ent, messageBuffer + outEnts++);
            }
        }
        ((u32*)buff)[0] = outEnts;

        sendto(SERVER->socket,
            buff, sizeof(buff),
            0, (struct sockaddr*)&SERVER->client, sizeof(SERVER->client)
        );
    }
}

#endif
