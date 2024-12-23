#include <iostream>
#include <stdlib.h>
#include <winsock2.h>
#include <cstring>
#pragma comment(lib,"ws2_32.lib")

using namespace std;
//tring un[100]= {"mike"};
//string pw[100]= {"test"};
int main(int argc, char* argv[])
{
    system("chcp 65001"); // 设置中文
    //初始化WSA
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
    //将本地址的IP和端口与套接字绑定
    sockaddr_in sin;
    sin.sin_family = AF_INET;//代表所属地址家族是TCP/IP地址家族
    sin.sin_port = htons(8888);//端口号，htons:将主机无符号短整型数转换成网络字节顺序
    sin.sin_addr.S_un.S_addr = INADDR_ANY;//任意地址
    if(bind(s, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)//绑定
    {
        cout<<"bind error !"<<endl;
    }
    //接收数据
    //SOCKET sClient;
    sockaddr_in addr;
    int nAddrlen = sizeof(addr);
    char revData[255];
    char sendData[255];
    SOCKET cur=INVALID_SOCKET;
    cout<<"————————服务器启动——————————"<<endl;
    while(true){
        int ret1 = recvfrom(s, revData, 255, 0, (sockaddr*)&addr, &nAddrlen);
        if(ret1 > 0)
        {
            revData[ret1] = 0x00;//为防止打印出错,把字符串结尾设为0x00
            cout<<"从客户端接受到的信息:"<<revData<<endl;
            if (strcmp(revData, "bye") == 0)
            {
                ::closesocket(s);
                return 0;
            }
        }
        cin>>sendData;
        sendto(s, sendData, strlen(sendData), 0, (sockaddr*)&addr, sizeof(addr));
        cout<<"服务器发送信息:"<<sendData<<endl;
        if (strcmp(sendData, "bye") == 0)
        {
            ::closesocket(s);
            return 0;
        }
    }
        //closesocket(sClient);

    closesocket(s);
    WSACleanup();
    system("pause");
    return 0;
}