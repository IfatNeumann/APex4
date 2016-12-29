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
    int id, age, experience, texiId;
    char status,dummy;
    Client client;
    Driver* p;
    //cin >> id >> dummy >> age >> dummy >> status >> dummy >> experience >> dummy >> texiId;
    p = client.createDriver(id, age, status, experience, texiId);
//    const char* ip_address = "127.0.0.1";
//    const int port_no = 5678;
//    int sock = socket(AF_INET, SOCK_DGRAM, 0);
//    if (sock < 0) {
//        perror("error creating socket");
//    }
//    struct sockaddr_in sin;
//    memset(&sin, 0, sizeof(sin));
//    sin.sin_family = AF_INET;
//    sin.sin_addr.s_addr = inet_addr(ip_address);
//    sin.sin_port = htons(port_no);
//    char data[] = "hello";
//    int data_len = sizeof(data);
//    int sent_bytes = sendto(sock, data, data_len, 0, (struct sockaddr *) &sin, sizeof(sin));
//    if (sent_bytes < 0) {
//        perror("error writing to socket");
//    }
//    struct sockaddr_in from;
//    unsigned int from_len = sizeof(struct sockaddr_in);
//    char buffer[4096];
//    int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
//    if (bytes < 0) {
//        perror("error reading from socket");
//    }
//    cout << "The server sent: " << buffer << endl;
//    close(sock);
    Driver p = client.createDriver();
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << p;
    s.flush();

    cout << serial_str << endl;

    Driver *p2;
    boost::iostreams::basic_array_source<char> device(serial_str.c_str(), serial_str.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> p2;

    delete p;
    delete p2;

    return 0;
}

Driver* Client::createDriver(int id,int age,char status,int experience,int taxiId){
    MaritalStatus maritalStatus =MaritalStatus (status);
    Driver* newDriver = new Driver(id,age,maritalStatus,experience,taxiId);
    return newDriver;
}