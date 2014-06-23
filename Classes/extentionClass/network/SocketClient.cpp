
#include "SocketClient.h"
#include "MessageHandler.h"

#include "MSAutoReleasePool.h"
#include "message.h"
#include <errno.h>
#include <signal.h>
#include "CData.h"
#include "json.h"

SocketClient::SocketClient(string host, int port):
m_iState(SocketClient_WAIT_CONNECT), // 这种写法相当于初始化
m_cbRecvBuf(1024*60),m_cbSendBuf(1024*60)
{
	m_isvalidSeq = false;
	memset(m_sabcde, 0, 6*8);
	
    pthread_mutex_init (&m_sendqueue_mutex,NULL);
	pthread_mutex_init(&m_thread_cond_mutex,NULL);
	pthread_cond_init(&m_threadCond, NULL);
	
	m_hSocket = -1;
	
	this->m_host = host;
	this->m_iport = port;
	
	m_bThreadRecvCreated = false;
	m_bThreadSendCreated = false;
    
    
}

void SocketClient::start(){
	if(!m_bThreadSendCreated){
		pthread_create( &pthread_t_send, NULL,ThreadSendMessage, this);
		m_bThreadSendCreated = true;
	}
}

bool SocketClient::isWaitConnect(){
	return m_iState == SocketClient_WAIT_CONNECT;
}
SocketClient::~SocketClient()
{
	m_iState = SocketClient_DESTROY;
	if( m_hSocket!=-1)
		close(m_hSocket);
	
	pthread_mutex_destroy(&m_sendqueue_mutex);
	pthread_mutex_destroy(&m_thread_cond_mutex);
	pthread_cond_destroy(&m_threadCond);
    
	
	while (!m_receivedMessageQueue.empty()) {
		Message* m = m_receivedMessageQueue.front();
		m_receivedMessageQueue.pop();
		SAFE_DELETE_ELEMENT(m);
	}
	
	while (!m_sendMessageQueue.empty()) {
		Message* m = m_sendMessageQueue.front();
		m_sendMessageQueue.pop();
		SAFE_DELETE_ELEMENT(m);
	}
    
}

Message* constructErrorMessage(int type,int errCode,string error){
	
	Message* msg = new Message();
    
	
	return msg;
}

int SocketClient::bytesToInt(byte* bytes)
{
    
    int addr = bytes[3] & 0xFF;
    
    addr |= ((bytes[2] << 8) & 0xFF00);
    
    addr |= ((bytes[1] << 16) & 0xFF0000);
    
    addr |= ((bytes[0] << 24) & 0xFF000000);
    
    return addr;
    
}

byte* SocketClient::intToByte(int i)
{
    
    byte* abyte0 = new byte[4];
    
    abyte0[3] = (byte) (0xff & i);
    
    abyte0[2] = (byte) ((0xff00 & i) >> 8);
    
    abyte0[1] = (byte) ((0xff0000 & i) >> 16);
    
    abyte0[0] = (byte) ((0xff000000 & i) >> 24);
    
    return abyte0;
    
}

Message* SocketClient::constructMessage(Json::Value json_temp,int commandId)
{
    Message* msg = new Message();
    
    msg->msgType = commandId;
    
    msg->json_temp = json_temp;
    
	return msg;
}




void SocketClient:: stop(boolean b){
	m_iState = SocketClient_DESTROY;
	
	{
		MyLock lock(&m_thread_cond_mutex);
		pthread_cond_signal(&m_threadCond);
	}
	if(m_bThreadRecvCreated)
		pthread_join(pthread_t_receive, NULL);
	pthread_join(pthread_t_send, NULL);
}



bool SocketClient::connectServer()
{
    
	if( m_host.length() < 1 || m_iport == 0) return false;
    
    socket = new ODSocket();
	socket->Init();
	socket->Create(AF_INET,SOCK_STREAM,0);
    
    bool isConnet = socket->Connect("127.0.0.1",9999);

	if (!isConnet)
	{
		printf("socket connect error:%d\n",errno);
		return false;
	}
    
	
	if( !m_bThreadRecvCreated ){
        // 创建一个线程 参数依次为：线程标识、线程参数、入口函数、入口函数参数
		if(pthread_create( &pthread_t_receive, NULL,ThreadReceiveMessage, this)!=0)
			return false;
		m_bThreadRecvCreated = true;
	}
    
	m_iState = SocketClient_OK;
    
	return true;
}

void SocketClient::sendMessage_(Message* msg,bool b)
{
	if(m_iState == SocketClient_DESTROY){
		delete msg;
		return;
	}
    Json::Value message;
    
    message["msgType"]=msg->msgType;
    message["data"] = msg->json_temp;

    Json::FastWriter fast_writer;
    string str_value = fast_writer.write(message);
    
    log("sendMessage :%s", str_value.c_str());
//    socket->Send(test.c_str(), b);
//    std::string testmsg="{'id':1,'msgType':1101,'name':'wangfeng','QQNum':'972341215'}";
    
    socket->Send(str_value.c_str(),strlen(str_value.c_str()) + 1,0);
	
    {
		MyLock lock(&m_sendqueue_mutex);
		m_sendMessageQueue.push(msg);
	}
	if( m_iState == SocketClient_OK)
	{
		MyLock lock(&m_thread_cond_mutex);
		pthread_cond_signal(&m_threadCond);
	}
	
}

void* SocketClient::ThreadSendMessage(void *p){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	MSAutoReleasePool POOL;
#endif
	SocketClient* This = static_cast<SocketClient*>(p) ;
	
	while(This->m_iState == SocketClient_WAIT_CONNECT && !This->connectServer()){
			This->m_iState = SocketClient_DESTROY;
			string error("连网失败,请检查网络设置");
			{
				MyLock lock(&This->m_sendqueue_mutex);
                
				This->m_receivedMessageQueue.push(constructErrorMessage(TYPE_SELF_DEINE_MESSAGE_CONNECT_FAIL,errno,error));
			}
        
			return ((void *)0);
		
	}
	
	return (void*)0;
}
bool g_bcheckReceivedMessage = true;
void* SocketClient::ThreadReceiveMessage(void *p)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	MSAutoReleasePool POOL;
#endif
//	fd_set fdRead;
	
	struct timeval	aTime;
	aTime.tv_sec = 1;
	aTime.tv_usec = 0;
    
//	//最大多少秒，连接上收不到数据就提示用户，重新登录
//	int maxIdleTimeInSeconds = 60*3;
//	
//	//最大多少秒，连接上收不到数据就提示用户，选择重连
//	int hint2TimeInSeconds = 60;
//	
//	
//	//多长时间没有收到任何数据，提示用户
//	int hintTimeInSeconds = 30;
	
	struct timeval lastHintUserTime;
	struct timeval lastReceiveDataTime;
//	struct timeval now;
	
	gettimeofday(&lastReceiveDataTime, NULL);
	lastHintUserTime = lastReceiveDataTime;
	
	SocketClient* This = static_cast<SocketClient*>(p) ;
	

    
	while (This->m_iState != SocketClient_DESTROY)
	{
        
		if( This->m_iState != SocketClient_OK){
			usleep(1000);
			continue;
		}
		
        
        int ret =  2;//select(This->m_hSocket+1,&fdRead,NULL,NULL,&aTime);
        
		if (ret == -1 )
		{
			if(errno == EINTR){
				printf("======   收到中断信号，什么都不处理＝＝＝＝＝＝＝＝＝");
			}else{
				This->m_iState = SocketClient_DESTROY;
				MyLock lock(&This->m_sendqueue_mutex);
				This->m_receivedMessageQueue.push(constructErrorMessage(TYPE_SELF_DEINE_MESSAGE_CONNECT_TERMINATE,errno,"连接异常中断"));
				return ((void *)0);
			}
		}
	
		if (ret > 0)
		{
//			if (FD_ISSET(This->m_hSocket,&fdRead))
//			{
            
            char recvBuf[1024] = "*";
            
            // 接收数据并处理
            bool a = true;
            while (a) {
                int b = This->socket->Recv(recvBuf,1024,0);
                a = b < 0;
                log("Rev%d", a);
            }

            string sp = This->prepareChar(recvBuf);
           
            rapidjson::Document d2;
            rapidjson::Value data;
            int messageType;
            d2.Parse<rapidjson::kParseDefaultFlags>(sp.c_str());
            
            data = d2["data"];
            messageType = data["msgType"].GetInt();
            Message* message = new Message();
            
            message->msgType = messageType;
            message->data = data.GetString();
            log("msgType: %d \n",message->msgType);
            if(message->msgType==218){
                CData::getCData()->m_newlevel_dic->setObject(message, 218);
            }
            else{
                CData::getCData()->m_dictionary->setObject(message,message->msgType);
            }
     
        }
        
	}
    
	return (void*)0;
}
//获取服务器包
Message* SocketClient::pickReceivedMessage(){
	Message* msg = NULL;
	MyLock lock(&m_sendqueue_mutex);
	if( m_receivedMessageQueue.size()>0){
		
		msg = m_receivedMessageQueue.front();
        
	}
	
	return msg;
}
Message* SocketClient::popReceivedMessage(){
	Message* msg = NULL;
	MyLock lock(&m_sendqueue_mutex);
	if( m_receivedMessageQueue.size()>0){
		
		msg = m_receivedMessageQueue.front();
		m_receivedMessageQueue.pop();
        
	}
    
	
	return msg;
}

void SocketClient::pushReceivedMessage(Message* msg){
	MyLock lock(&m_sendqueue_mutex);
	m_receivedMessageQueue.push(msg);
}

long long SocketClient::getSeq(){
	if( m_isvalidSeq ){
		long long a = m_sabcde[1];
		long long b = m_sabcde[2];
		long long c = m_sabcde[3];
		long long d = m_sabcde[4];
		m_sabcde[0] = (long long)(a*2+b+c*3+d);
		m_sabcde[1] = a^b+b|c+3+d;
		m_sabcde[2] = b-a+d*123;
		m_sabcde[3] = (c%123456)+a*b+(long long)sqrt((double)abs(d));
		m_sabcde[4] = (long long)(a*1.233f+b*0.45456f+c*d+9);
	}
	return m_sabcde[0];
}

void SocketClient::swhlie(int commandId)
{
    
    
}


string SocketClient::prepareChar(char *ps){
    
    while (ps[0] != '{')
    {
        ps++;
    }
    std::string str(ps);
    
    return str;
}

///////////////////server////////////
SocketServer* g_socketServer = new SocketServer();

SocketServer::SocketServer(){
    isStartedServer = false;
    isExistOtherServer = false;
    server_socket = 0;
    isStartServerBindFail = false;
}

SocketServer::~SocketServer(){
    if( server_socket!=0){
        close(server_socket);
        server_socket=0;
    }
}


void* ThreadListen(void* p){
    SocketServer* serv = (SocketServer*)p;
    char tmp[256]="";
    while (serv->isStartedServer) //服务器端要一直运行
    {
        //定义客户端的socket地址结构client_addr
        struct sockaddr_in client_addr;
        socklen_t length = sizeof(client_addr);
        //接受一个到server_socket代表的socket的一个连接
        //如果没有连接请求,就等待到有连接请求--这是accept函数的特性
        //accept函数返回一个新的socket,这个socket(new_server_socket)用于同连接到的客户的通信
        //new_server_socket代表了服务器和客户端之间的一个通信通道
        //accept函数把连接到的客户端信息填写到客户端的socket地址结构client_addr中
        int new_server_socket = accept(serv->server_socket,(struct sockaddr*)&client_addr,&length);
        if ( new_server_socket < 0)
        {
            //if( DEBUG)            printf("[SocketServer] Server Accept Failed!\n");
            continue;
        }
        memset(tmp, 0, 256);
        int rt = recv(new_server_socket, tmp, 256,0);
        //关闭与客户端的连接
        close(new_server_socket);
        if( rt>0 && strcmp(tmp , "kill wxs" ) == 0){
            serv->killed();
            //if( DEBUG)        printf("[SocketServer] recv message [%s] from new client!\n",tmp);
            break;
        }
    }
    //关闭监听用的socket
    if( serv->server_socket !=0 ){
        close(serv->server_socket);
        serv->server_socket = 0;
    }
    serv->isStartedServer = false;
    serv->isStartServerBindFail = false;
    return 0;
}


void SocketServer::killed(){
    isStartedServer = false;
    isStartServerBindFail = false;
}



bool SocketServer::startServer(){
    if( server_socket!=0){
        close(server_socket);
        server_socket= 0;
    }
    if( !isStartedServer){
        usleep(1000000); //使线程休眠，等同于sleep不过sleep不跨平台，只适用于window
        isStartServerBindFail = false;
        struct sockaddr_in server_addr;
        int HELLO_WORLD_SERVER_PORT = 43067;
        memset(&server_addr,0,sizeof(server_addr)); //把一段内存区的内容全部设置为0
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = htons(INADDR_ANY);
        server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);
        //创建用于internet的流协议(TCP)socket,用server_socket代表服务器socket
        
        
        ODSocket* socket = new ODSocket();
        socket->Init();
        socket->Create(AF_INET,SOCK_STREAM,0);
        bool isConnet = socket->Connect( "127.0.0.1", 9998);
        
        if (!isConnet) return  false;
        
        int opt =1;
        setsockopt(server_socket,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
        
        //把socket和socket地址结构联系起来
        //        if( bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr)))
        //        {
        //            isStartServerBindFail = true;
        //
        //            return false;
        //        }
        //        //server_socket用于监听
        //        if ( listen(server_socket, 5) )
        //        {
        //            return false;
        //        }
        isStartedServer = true;
        pthread_t t;
        pthread_create( &t, NULL,ThreadListen, this);
    }
    return true;
}

void SocketServer::killOtherServer(){
    isExistOtherServer = false;
    int client_socket = socket(AF_INET,SOCK_STREAM,0);
    if( client_socket < 0)
    {
        return;
    }
    
    int HELLO_WORLD_SERVER_PORT = 43067;
    
    sockaddr_in SocketAddr;
	memset(&SocketAddr,0,sizeof(SocketAddr));
	SocketAddr.sin_family=AF_INET;
	SocketAddr.sin_port=htons(HELLO_WORLD_SERVER_PORT);
	SocketAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	memset(&(SocketAddr.sin_zero),0, 8);
    
	int iErrorCode=0;
    
    
	iErrorCode= connect(client_socket,(sockaddr*)&SocketAddr,sizeof(SocketAddr));
	if (iErrorCode==-1)
	{
        // if( DEBUG) printf("[CheckServer] socket server not exist error:%d\n",errno);
        close( client_socket);
		return;
	}
    const char *tmp = "kill wxs";
    write(client_socket, tmp, strlen(tmp));
    // if( DEBUG)   printf("[CheckServer] socket server : kill  server\n");
    
    
    char str[256];
    memset(str, 0, 256);
    int rt = recv(client_socket, str, 256, 0);
    
    close( client_socket);
    
    if( rt>0 ){
        isExistOtherServer = true;
        // if( DEBUG) printf("[SocketServer] recv message [%s] from server!\n",str);
    }
    
    
}


