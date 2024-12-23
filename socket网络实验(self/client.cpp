#include "initsocket.h"
#include <iostream>
#include <string>
#include <thread>

int main(){
    InitSock* So=new InitSock();

    //创建套接字
    SOCKET client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(client_socket==INVALID_SOCKET){
        std::cout<<"Socket initialization failed"<<std::endl;
        delete So;
    }

    //给套接字绑定ip地址与端口
    sockaddr_in clientAddr;
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(8080);
    clientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(connect(client_socket, (struct sockaddr*)&clientAddr, sizeof(clientAddr))==SOCKET_ERROR){
        std::cout<<"Client connection failed"<<std::endl;
        delete So;
        return 0;
        system("pause");
    }
    else{
        std::cout<<"Client connected successfully"<<std::endl;
    }

    std::string name;
    std::cout<<"Please enter your name:"<<std::endl;
    std::getline(std::cin, name);
    send(client_socket, name.data(),100,0);

    auto thread_func=[&](){     //由于主线程始终处于发送数据的循环中，分出一个线程来进行接收数据
        char recvbuf[100]={0};
        while(1){
            int len=recv(client_socket, recvbuf, 100, 0);
            if(len>0){
                std::cout<<recvbuf<<std::endl<<std::endl;
            }
            if(len==0 || len==SOCKET_ERROR){
                break;
            }
        }
    };

    //创建线程来接收数据
    std::thread recv(thread_func);
    recv.detach();

    //主线程循环发送数据
    int len=0;
    while(1){
        char sendbuf[100]={0};
        std::cin.getline(sendbuf, 100);
        len = send(client_socket,sendbuf,100,0);
        std::cout<<"user<"<<name<<"> "<<sendbuf<<std::endl<<std::endl;
        if(len==0 || len==SOCKET_ERROR){
            break;
        }
    }

    //关闭链接
    closesocket(client_socket);
    delete So;
    return 0;
}