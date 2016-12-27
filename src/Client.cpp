#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "Client.h"
#include "MaritalStatus.h"
using namespace std;
Client::Client(){
    this->driver = new Driver(0,0,MaritalStatus::SINGLE,0,NULL,NULL);
}
Client::~Client(){

}
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
    cin >> id >> dummy >> age >> dummy >> status >> dummy >> experience >> dummy >> texiId;
    this->createDriver(id, age, status, experience, texiId);
    return 0;
}

void Client::createDriver(int id,int age,char status,int experience,int texiId){
    MaritalStatus maritalStatus =MaritalStatus (status);
    Cab* texiInfo;
    for(int i=0;i<this->cabsVector.size();i++){
        if(this->cabsVector[i]->getId()==texiId){
            texiInfo = this->cabsVector[i];
        }
    }
    Driver* newDriver = new Driver(id,age,maritalStatus,experience,texiInfo,grid->getNode(Point(0,0)));
    this->myTaxiCenter->addDriver(newDriver);
}