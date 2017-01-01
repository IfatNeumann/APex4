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
    char status,dummy,*buffer;
    Client client;
    Driver* driver;
    cin >> id >> dummy >> age >> dummy >> status >> dummy >> experience >> dummy >> taxiId;
    driver = client.createDriver(id, age, status, experience, taxiId);
    Socket* socket= new Udp(false,5006);
    socket->initialize();

    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driver;
    s.flush();
    socket->sendData(serial_str);

    int dataSize=socket->reciveData(buffer, 4096);
    Cab *taxi;
    boost::iostreams::basic_array_source<char> device(buffer, dataSize);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> taxi;
    driver->setTaxi(taxi);

    delete socket;
    delete driver;
    delete taxi;

    return 0;
}


Driver* Client::createDriver(int id,int age,char status,int experience,int taxiId){
    MaritalStatus maritalStatus =MaritalStatus (status);
    Driver* newDriver = new Driver(id,age,maritalStatus,experience,taxiId);
    return newDriver;
}