#include <iostream>
#include <stdlib.h>
#include <winsock2.h>
#include <cstring>
#pragma comment(lib,"ws2_32.lib")

using namespace std;
int main()
{   
    system("chcp 65001"); // 设置中文
    WORD sockVersion = MAKEWORD(2,2);//定义版本号码
    WSADATA wsaData;//结构体，包含加载库版本的相关信息
    if(WSAStartup(sockVersion, &wsaData))return 0;//返回0，表示初始化成功，否则程序结束

    //创建socket套接字
    SOCKET s = socket(AF_INET, SOCK_DGRAM,IPPROTO_UDP);
    if(s == INVALID_SOCKET)
    {
        cout<<"socket error !"<<endl;
        return 0;
    }
    // 填写远程地址信息 
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    int nLen = sizeof(addr);// 发送数据
    char revData[255];
    char sendData[255];
    cout<<"-----------------我是客户端-------------------------"<<endl;
    while (TRUE)
    {
    int nRecv = ::recvfrom(s,revData,255,0,(sockaddr*)&addr,&nLen);
    if(nRecv>0)
    {
        revData[nRecv] = 0x00;
        cout<<"从服务端接受到的信息:"<<revData<<endl;
        if (strcmp(revData, "bye") == 0)
        {
            closesocket(s);
            return 0;
        }
    }//发送数据           
    // scanf("%s", sendbuffer);
    cin>>sendData;
    ::sendto(s,sendData, strlen(sendData),0,(sockaddr*)&addr,sizeof(addr));
    //ystem("color 0F")；
    cout<<"客户端发送信息:"<<sendData<<endl;
    if (strcmp(sendData,"bye")==0)
    {
        closesocket(s);
        return 0;
        }
    }
    return 0;
}