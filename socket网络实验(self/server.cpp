#include "initsocket.h"
#include <iostream>
#include <thread>
#include <map>
#include <string>
#include <sstream>
#include <functional>

std::map<SOCKET, std::string> client_; //存储客户端socket与客户端名字

int main(){
    InitSock *So=new InitSock();

    //创建socket套接字
    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(server_socket==INVALID_SOCKET){
        std::cout<<"socket initialization failed"<<std::endl;
        delete So;
    }
    else{
        std::cout<<"socket initialized successfully"<<std::endl;
    }

    //给套接字绑定ip地址与端口
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(server_socket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR){
        std::cout<<"bind error"<<std::endl;
        delete So;
    }
    else{
        std::cout<<"bind successfully"<<std::endl;
    }

    //监听端口
    if(listen(server_socket, 5) == SOCKET_ERROR){
        std::cout<<"listen error"<<std::endl;
        delete So;
    }
    else{
        std::cout<<"listening ..."<<std::endl;
    }

    //接收并处理客户端请求
    while(1){
        sockaddr_in clientAddr;
        int addrLen=sizeof(clientAddr);
        SOCKET client_socket=accept(server_socket, (struct sockaddr *)&clientAddr, &addrLen);
        if(client_socket==INVALID_SOCKET){  //接收失败
            std::cout<<"receive error"<<std::endl;
            delete So;
            return 0;
        }
        else {
            std::cout<<"new client connected"<<std::endl;
        }
        auto thread_func = [&](){
            //成功连接到客户端
            char buf_recv[100]={0};
            int len = recv(client_socket, buf_recv, sizeof(buf_recv), 0);
            client_[client_socket] = std::string(buf_recv);
            std::cout<<"user:<"<<client_[client_socket]<<"> connected"<<std::endl;  //server端显示用户加入
            std::string buf_send;
            std::stringstream ss(buf_send);
            ss<<"user:<"<<client_[client_socket]<<"> connected"<<std::endl;
            send(client_socket, ss.str().c_str(), ss.str().size(), 0);      //客户端显示用户加入
            for(auto it=client_.begin();it!=client_.end();it++){            //向所有客户端转发消息
                if(it->first!=client_socket){
                    send(it->first, ss.str().c_str(), ss.str().size(), 0);
                }
            }

            //服务端收发消息
            len=0;
            while(1){
                char buf_msg[100]={0};
                len = recv(client_socket, buf_msg, sizeof(buf_msg), 0);
                std::cout<<"receive message from user:<"<<client_[client_socket]<<">"<<buf_msg<<std::endl;
                std::stringstream ss_msg(buf_send);
                ss_msg<<"user:<"<<client_[client_socket]<<">"<<buf_msg<<std::endl;
                for(auto it=client_.begin();it!=client_.end();it++){        //向所有客户端转发消息
                    if(it->first!=client_socket){
                        send(it->first, ss_msg.str().c_str(), ss_msg.str().size(), 0);
                    }
                }
                if(len==0||len==SOCKET_ERROR){
                    break;
                }
            }

            //关闭与客户端的连接
            closesocket(client_socket);
            std::cout<<"user:<"<<client_[client_socket]<<"> disconnected"<<std::endl;
            client_.erase(client_socket);
        };

        
        std::thread th_(thread_func);
        th_.detach();   //detach线程，主线程不等待线程结束
    }

    delete So;
    return 0;
}