#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "Client.h"
#include "../sockets/Udp.h"
using namespace std;
int main() {
    int id, age, experience, taxiId;
    char status,dummy;
    Client client;
    Driver* p;
    cin >> id >> dummy >> age >> dummy >> status >> dummy >> experience >> dummy >> taxiId;
    p = client.createDriver(id, age, status, experience, taxiId);
    Socket* socket= new Udp(false,5006);
    socket->initialize();

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
    delete socket;
    delete p;
    delete p2;

    return 0;
}

Driver* Client::createDriver(int id,int age,char status,int experience,int taxiId){
    MaritalStatus maritalStatus =MaritalStatus (status);
    Driver* newDriver = new Driver(id,age,maritalStatus,experience,taxiId);
    return newDriver;
}