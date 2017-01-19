#include <iostream>
#include "Client.h"
#include "../sockets/Tcp.h"
#include "StandardCab.h"
#include "LuxuryCab.h"
#include <boost/serialization/export.hpp>
#include <boost/log/trivial.hpp>
BOOST_CLASS_EXPORT_GUID(StandardCab,"StandardCab")
BOOST_CLASS_EXPORT_GUID(LuxuryCab,"LuxuryCab")
using namespace std;
int main(int argc,char* argv[]) {
    int id, age, experience, taxiId, missionNum, dataSize;
    string ip = argv[1];
    int portNum = atoi(argv[2]);
    char status,dummy, buffer[4096];
    Client client;
    Driver* driver;
    Cab* taxi;
    TripInfo *tripInfo = NULL;
    Tcp* socket= new Tcp(false,portNum);
    socket->initialize();
    BOOST_LOG_TRIVIAL(debug)<<"client initialized!"<<endl;
    Node *endPoint = NULL,*currentPoint, *nextPoint = NULL;
    cin >> id >> dummy >> age >> dummy >> status >> dummy >> experience >> dummy >> taxiId;
    driver = client.createDriver(id, age, status, experience, taxiId);

    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driver;
    s.flush();
    socket->sendData(serial_str,0);
    BOOST_LOG_TRIVIAL(debug)<<"client sent driver!"<<endl;
    do {
        //receive mission number
        memset(buffer,0,4096);
        dataSize = socket->reciveData(buffer, 4096,0);
        string missionNumString = string(buffer);
        missionNum = stoi(missionNumString);
        BOOST_LOG_TRIVIAL(debug)<<"missionNum: "<<missionNum;

        BOOST_LOG_TRIVIAL(debug)<<"send between two receives";
        socket->sendData("accepted",0);
        switch(missionNum) {
            //receive taxi
            case (2): {
                memset(buffer,0,4096);
                dataSize = socket->reciveData(buffer, 4096,0);
                boost::iostreams::basic_array_source<char> device(buffer, dataSize);
                cout << "BREAK1!" << endl;
                cout << buffer << endl;
                boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
                boost::archive::binary_iarchive ia(s2);
                ia >> taxi;
                BOOST_LOG_TRIVIAL(debug)<<"client received taxi!"<<endl;
                driver->setTxCabInfo(taxi);
    		    cout << "BREAK2!" << endl;
                //receiving the current point
                memset(buffer,0,sizeof(buffer));
                dataSize = socket->reciveData(buffer, 4096,0);
                boost::iostreams::basic_array_source<char> device3(buffer, dataSize);
                boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s4(device3);
                boost::archive::binary_iarchive ic(s4);
                ic >> currentPoint;
                BOOST_LOG_TRIVIAL(debug)<<"client received current point:"<<endl;
                currentPoint->getPoint().printPoint();
                driver->setCurrentPoint(currentPoint);
                //send driver *with* his taxi
                std::string serial_str8;
                boost::iostreams::back_insert_device<std::string> inserter8(serial_str8);
                boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s8(inserter8);
                boost::archive::binary_oarchive ob(s8);
                ob << driver;
                BOOST_LOG_TRIVIAL(debug)<<"client send driver with taxi!"<<endl;
                s8.flush();
                socket->sendData(serial_str8,0);
                break;
            }
                //receive tripInfo
            case (3): {
                BOOST_LOG_TRIVIAL(debug)<<"client receive trip info!"<<endl;
                memset(buffer,0,sizeof(buffer));
                dataSize = socket->reciveData(buffer, 4096,0);
                boost::iostreams::basic_array_source<char> device2(buffer, dataSize);
                boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s3(device2);
                boost::archive::binary_iarchive ib(s3);
                if(tripInfo!=NULL){
                    delete(tripInfo);
                }
                ib >> tripInfo;
                driver->setMyTripInfo(tripInfo);
                break;
            }
                //receive destination point
            case (4): {
                BOOST_LOG_TRIVIAL(debug)<<"client receive dest point!"<<endl;
                memset(buffer,0,sizeof(buffer));
                dataSize = socket->reciveData(buffer, 4096,0);
                boost::iostreams::basic_array_source<char> device3(buffer, dataSize);
                boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s4(device3);
                boost::archive::binary_iarchive ic(s4);
                if(endPoint!=NULL){
                    delete(endPoint);
                }
                ic >> endPoint;
                break;
            }
                //move one step
            case (5): {

                BOOST_LOG_TRIVIAL(debug)<<"client -move one step!"<<endl;
                //receive next point
                memset(buffer,0,sizeof(buffer));
                dataSize = socket->reciveData(buffer, 4096,0);
                boost::iostreams::basic_array_source<char> device4(buffer, dataSize);
                boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s5(device4);
                boost::archive::binary_iarchive ie(s5);
                if(nextPoint!=NULL){
                    delete(nextPoint);
                }
                ie >> nextPoint;
                driver->setCurrentPoint(nextPoint);
                BOOST_LOG_TRIVIAL(debug)<<"client -print point:"<<endl;
                nextPoint->getPoint().printPoint();
                if((endPoint!=NULL)&&(driver->getCurrentPoint()->getPoint().isEqualTo(endPoint->getPoint()))){
                    driver->setMyTripInfo(NULL);
                }
                break;
            }
                //delete
            case (7): {
                BOOST_LOG_TRIVIAL(debug)<<"client - delete"<<endl;
                delete endPoint;
                delete currentPoint;
                delete nextPoint;
                delete taxi;
                delete tripInfo;
                delete socket;
                delete driver;
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
