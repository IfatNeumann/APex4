#include <iostream>
#include "Client.h"
#include "../sockets/Udp.h"
#include "StandardCab.h"
#include "LuxuryCab.h"
#include <boost/serialization/export.hpp>
BOOST_CLASS_EXPORT_GUID(StandardCab,"StandardCab")
BOOST_CLASS_EXPORT_GUID(LuxuryCab,"LuxuryCab")
using namespace std;
int main(int argc,char* argv[]) {
    int id, age, experience, taxiId;
    string ip = argv[1];
    int portNum = atoi(argv[2]);
    char status,dummy;
    char buffer[4096];
    Client client;;
    Driver* driver;
    Cab* taxi;
    TripInfo *tripInfo;
    Socket* socket= new Udp(false,portNum);
    socket->initialize();
    int missionNum;
    Node *endPoint;

    cin >> id >> dummy >> age >> dummy >> status >> dummy >> experience >> dummy >> taxiId;
    driver = client.createDriver(id, age, status, experience, taxiId);
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driver;
    s.flush();
    socket->sendData(serial_str);

    //receive mission number
    int dataSize;
    string missionNumString = string(buffer);
    missionNum = stoi(missionNumString);

    do {
        switch(missionNum) {
            //receive taxi
            case (2): {
                dataSize = socket->reciveData(buffer, 4096);
                boost::iostreams::basic_array_source<char> device(buffer, dataSize);
                boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
                boost::archive::binary_iarchive ia(s2);
                ia >> taxi;
                driver->setTxCabInfo(taxi);
                //send driver *with* his taxi
                std::string serial_str8;
                boost::iostreams::back_insert_device<std::string> inserter8(serial_str8);
                boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s8(inserter8);
                boost::archive::binary_oarchive ob(s8);
                ob << driver;
                s8.flush();
                socket->sendData(serial_str8);

                break;
            }
            //receive tripInfo
            case (3): {
                dataSize = socket->reciveData(buffer, 4096);
                boost::iostreams::basic_array_source<char> device2(buffer, dataSize);
                boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s3(device2);
                boost::archive::binary_iarchive ib(s3);
                ib >> tripInfo;
                driver->setMyTripInfo(tripInfo);
                break;
            }
            //receive destination point
            case (4): {
                dataSize = socket->reciveData(buffer, 4096);
                boost::iostreams::basic_array_source<char> device3(buffer, dataSize);
                boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s4(device3);
                boost::archive::binary_iarchive ic(s4);
                ic >> endPoint;
                break;
            }
            //move one step
            case (5): {
                Node *nextPoint;
                //receive next point
                dataSize = socket->reciveData(buffer, 4096);
                do {
                    boost::iostreams::basic_array_source<char> device4(buffer, dataSize);
                    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s5(device4);
                    boost::archive::binary_iarchive ie(s5);
                    ie >> nextPoint;
                    driver->setCurrentPoint(nextPoint);
                    //receive next point
                    dataSize = socket->reciveData(buffer, 4096);
                } while (!(nextPoint->getPoint().isEqualTo(endPoint->getPoint())));
                //receive the last point (endPoint)
                boost::iostreams::basic_array_source<char> device4(buffer, dataSize);
                boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s5(device4);
                boost::archive::binary_iarchive ie(s5);
                ie >> nextPoint;
                driver->setCurrentPoint(nextPoint);
                break;
            }
            //delete
            case (7): {
                delete taxi;
                delete tripInfo;
                delete socket;
                //delete driver;
                return 0;
            }

        }
    }while(missionNum!=7);
    return 0;
}


Driver* Client::createDriver(int id,int age,char status,int experience,int taxiId){
    MaritalStatus maritalStatus =MaritalStatus (status);
    Driver* newDriver = new Driver(id,age,maritalStatus,experience,taxiId);
    return newDriver;
}