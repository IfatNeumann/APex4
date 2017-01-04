#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "MainFlow.h"
#include <boost/serialization/export.hpp>
BOOST_CLASS_EXPORT_GUID(StandardCab,"StandardCab")
BOOST_CLASS_EXPORT_GUID(LuxuryCab,"LuxuryCab")
using namespace std;
int main(int argc,char* argv[]) {
    int portNum = atoi(argv[1]);
    MainFlow* mainflow = new MainFlow();
    mainflow->mainFlow(portNum);
    delete mainflow;
    return 0;
}