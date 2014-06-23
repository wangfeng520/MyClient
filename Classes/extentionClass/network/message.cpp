
#include "message.h"
#include "SocketClient.h"

Message::Message():data(NULL){
    
}
Message::~Message()
{
	//printf("Message::~Message() %p\n",this);
	if (data!=NULL) {
		delete[] data;
	}
}

