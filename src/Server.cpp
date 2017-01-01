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
int main() {

    MainFlow* mainflow = new MainFlow();
    mainflow->mainFlow();

//    const int server_port = 5678;
//    int sock = socket(AF_INET, SOCK_DGRAM, 0);
//    if (sock < 0) {
//        perror("error creating socket");
//    }
//    struct sockaddr_in sin;
//    memset(&sin, 0, sizeof(sin));
//    sin.sin_family = AF_INET;
//    sin.sin_addr.s_addr = INADDR_ANY;
//    sin.sin_port = htons(server_port);
//    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
//        perror("error binding to socket");
//    }
//    struct sockaddr_in from;
//    unsigned int from_len = sizeof(struct sockaddr_in);
//    char buffer[4096];
//    int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
//    if (bytes < 0) {
//        perror("error reading from socket");
//    }
//    cout << "The client sent: " << buffer << endl;
//    int sent_bytes = sendto(sock, buffer, bytes, 0, (struct sockaddr *) &from, sizeof(from));
//    if (sent_bytes < 0) {
//        perror("error writing to socket");
//    }
//    close(sock);
    return 0;
}