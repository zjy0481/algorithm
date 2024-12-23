//socket 初始化头文件
#ifndef _INITSOCKET_H_
#define _INITSOCKET_H_
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#pragma comment(lib,"WS2_32")
//链接到WS2_32.lib
class InitSock
{
public:
    InitSock(unsigned char minorVer = 2, unsigned char majorVer = 2)   //使用winsock2.2版本
    {
        // 初始化WS2_32.dll
        WSADATA wsaData;
        WORD sockVersion = MAKEWORD(minorVer, majorVer);        //使用MAKEWORD宏合成版本号
        if(WSAStartup(sockVersion, &wsaData) != 0)              //初始化winsock
        {
            std::cerr<<"WSAStartup failed!"<<std::endl;       //如果初始化失败，抛出错误信息
            exit(0);
        }
        else{
            std::cout<<"InitSock success!"<<std::endl;
        }
    }
    ~InitSock(){
        WSACleanup();       //释放资源，卸载Winsock DLL
    }
};
#endif