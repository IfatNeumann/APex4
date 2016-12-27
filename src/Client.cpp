#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "Client.h"
using namespace std;
int main() {

    const char* ip_address = "127.0.0.1";
    const int port_no = 5678;
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }
    /*struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(port_no);
    char data[] = "hello";
    int data_len = sizeof(data);
    int sent_bytes = sendto(sock, data, data_len, 0, (struct sockaddr *) &sin, sizeof(sin));
    if (sent_bytes < 0) {
        perror("error writing to socket");
    }
    struct sockaddr_in from;
    unsigned int from_len = sizeof(struct sockaddr_in);
    char buffer[4096];
    int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
    if (bytes < 0) {
        perror("error reading from socket");
    }
    cout << "The server sent: " << buffer << endl;
    close(sock);
*/
    int id, age, experience, texiId;
    char status,dummy;
    Client client;
    cin >> id >> dummy >> age >> dummy >> status >> dummy >> experience >> dummy >> texiId;
    client.createDriver(id, age, status, experience, texiId);
    return 0;
}

void Client::createDriver(int id,int age,char status,int experience,int taxiId){
    MaritalStatus maritalStatus =MaritalStatus (status);
    Driver* newDriver = new Driver(id,age,maritalStatus,experience,taxiId);
}