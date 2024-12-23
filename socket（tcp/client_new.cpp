#include <stdio.h>
#include <stdlib.h>
#include "afxres.h"
#include <winsock2.h> // winsock2的头文件
#include <iostream>
#include <map>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

map<SOCKET, string> client;
DWORD WINAPI Threadfun(LPVOID lpParameter);

int main()
{
    system("chcp 65001");

    // 加载winsock环境
    WSADATA wd;
    if (WSAStartup(MAKEWORD(2, 2), &wd) != 0) {
        cout << "加载网络环境失败" << endl;
        return 0;
    }
    else
        cout << "加载网络环境成功" << endl;

    // 创建套接字
    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) {
        cout << "创建套接字失败" << endl;
        WSACleanup();
    }
    else
        cout << "创建套接字成功" << endl;

    // 给套接字绑定ip地址和端口：bind函数
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8000);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int len = sizeof(sockaddr_in);
    if (connect(s, (SOCKADDR*)&addr, len) == SOCKET_ERROR) {
        cout << "客户端连接失败" << endl;
        WSACleanup();
        return 0;
    }
    else
        cout << "客户端连接成功" << endl;

    // 发送和接受数据即可
    string name;
    char bufrecv[100] = { 0 };
    cout << "请输入你的昵称：";
    getline(cin, name); // 读入一整行，可以有空格
    send(s, name.data(), 100, 0);
    int ret;

    // 建立连接后，创建线程用于接受数据，主线程用来发送数据
    CloseHandle(CreateThread(NULL, 0, Threadfun, (LPVOID)s, 0, NULL));

    // while循环发送数据
    ret = 0;
    do {
        char bufrecv[100] = { 0 };
        cin.getline(bufrecv, 100);
        ret = send(s, bufrecv, 100, 0);
    } while (ret != SOCKET_ERROR && ret != 0); // 如果连接被关闭，返回0，否则返回socket_error

    // 关闭连接，释放资源
    closesocket(s);
    WSACleanup();
    return 0;
}

DWORD WINAPI Threadfun(LPVOID lpParameter) {
    SOCKET c = (SOCKET)lpParameter;
    int ret = 0;
    do {
        char buf[100] = { 0 };
        ret = recv(c, buf, 100, 0);
        cout << buf << endl << endl;
    } while (ret != SOCKET_ERROR && ret != 0); // 如果连接被关闭，返回0，否则返回socket_error

    return 0;
}
