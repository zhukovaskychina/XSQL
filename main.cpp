#include <iostream>
#include "muduo/net/TcpServer.h"
#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <muduo/base/CurrentThread.h>
#include <server/XdbServer.h>

int main() {
    std::cout << "Hello, World!" << std::endl;
    muduo::net::EventLoop loop;
    muduo::net::InetAddress listenAddr(30002);
    XDBServer miniServer(&loop,listenAddr);
    miniServer.start();
    loop.loop();
    return 0;
}