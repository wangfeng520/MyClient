#include "SocketManager.h"


static SocketManager* instance = NULL;
SocketManager::SocketManager()
{
    

}

SocketManager* SocketManager::getInstance()
{
    if(instance == NULL)
    {
        instance = new SocketManager();
        
    }
    
    return instance;
}

void SocketManager::startSocket()
{
    
    log("-----SocketManager开始创建连接-------");
    
    _socket = new SocketClient("127.0.0.1",8888);

    _socket->start();
}

void SocketManager::sendMessage(Json::Value data,int commandId)
{
    
    Message *msg=_socket->constructMessage(data, commandId);
    
    
    
    _socket->sendMessage_(msg, false);
}




