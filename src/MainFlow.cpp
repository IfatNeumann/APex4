#include "MainFlow.h"
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "Client.h"
#include "../sockets/Udp.h"

MainFlow::MainFlow(){
    this->myTaxiCenter = new TaxiCenter();
    this->grid;
    this->cabsVector;
}

MainFlow::~MainFlow() {
 delete (myTaxiCenter);
    delete (grid);
for(int i=0;i<cabsVector.size();++i){
	delete cabsVector[i];
}
}

TaxiCenter* MainFlow::getTaxiCenter(){
    return this->myTaxiCenter;
}

vector<Cab*> MainFlow::getCabsVector(){
    return this->cabsVector;
}

void MainFlow::createCab(int idTaxi,int typeOfTaxi,char manufacturer,char color){
    Manufacturer taxiManufacturer= Manufacturer (manufacturer);
    Color taxiColor = Color (color);
    if (typeOfTaxi==1){
        StandardCab* newStandardCab = new StandardCab(idTaxi,typeOfTaxi,taxiManufacturer,taxiColor);
        cabsVector.push_back(newStandardCab);
    }
    else{
        LuxuryCab* newLuxuryCab = new LuxuryCab(idTaxi,typeOfTaxi,taxiManufacturer,taxiColor);
        cabsVector.push_back(newLuxuryCab);
    }
}

void MainFlow::createTripInfo(int tripId, int xStartPoint,int yStartPoint, int xEndPoint, int yEndPoint,
                                   int numOfpassn, double tariff, int timeOfStart){
    TripInfo* newTrip = new TripInfo(tripId,grid->getNode(Point(xStartPoint,yStartPoint)),
                                     grid->getNode(Point(xEndPoint,yEndPoint)),numOfpassn,tariff, timeOfStart);
    this->myTaxiCenter->addTrip(newTrip);
}

void MainFlow::createGrid(int gridX,int gridY){
    this->grid = new Grid(gridX,gridY);
    return;
}
Grid* MainFlow::getGrid(){
    return this->grid;
}

Cab* MainFlow::getCab(int texiId) {
    for(int i=0;i<this->cabsVector.size();i++){
        if(this->cabsVector[i]->getId()==texiId){
            return this->cabsVector[i];
        }
    }
}

void MainFlow::mainFlow(){
    int time=0;
    int gridXAxe,gridYAxe,numOfObstacles;
    int xPoint,yPoint;
    char dummy;
    int mission;
    char* buffer;
    Socket* socket= new Udp(true,5006);
    socket->initialize();

    //entered the size of the grid (map)
    cin >> gridXAxe >> gridYAxe;
    this->createGrid(gridXAxe,gridYAxe);
    //entered the numbers of the obstacles that will be at the map
    cin >> numOfObstacles;
    //add the obstacles to the map
    while(numOfObstacles>0){
        cin >> xPoint >> dummy >> yPoint;
        this->getGrid()->getNode(Point(xPoint,yPoint))->setIsObstacle();
        numOfObstacles--;
    }

    do{
        cin>>mission;
        switch (mission) {
            //this mission is for creating and adding a new driver to the game
            case 1: {
                int numOfDrivers;
                cin >> numOfDrivers;
                while(numOfDrivers) {
                    //receive the driver
                    socket->receiveData(buffer, 4096);
                    Driver *driver;
                    boost::iostreams::basic_array_source<char> device(buffer, 4096);
                    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
                    boost::archive::binary_iarchive ia(s2);
                    ia >> driver;
                    this->myTaxiCenter->addDriver(driver);
                    //find the taxi
                    Cab* taxi = this->getCab(driver->getTaxiId());
                    //send the taxi

                    std::string serial_str;
                    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
                    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
                    boost::archive::binary_oarchive oa(s);
                    oa << taxi;
                    s.flush();
                    socket->sendData(serial_str);
                    numOfDrivers--;
                    break;
                }
            }
                //this mission is for creating and adding a new trip to the game
            case 2: {
                int tripId, xStartPoint, yStartPoint, xEndPoint, yEndPoint, numOfpassn,timeOfStart;
                double tariff;
                cin >> tripId >> dummy >> xStartPoint >> dummy >> yStartPoint >> dummy >> xEndPoint >> dummy >> yEndPoint >>
                    dummy >> numOfpassn >> dummy >> tariff >> dummy >> timeOfStart;
                this->createTripInfo(tripId, xStartPoint, yStartPoint, xEndPoint, yEndPoint, numOfpassn, tariff, timeOfStart);
                break;
            }
            //this mission is for creating and adding a new vehicle to the game
            case 3: {
                int idTaxi;
                int typeOfTaxi;
                char manufacturer, color;
                cin >> idTaxi >> dummy >> typeOfTaxi >> dummy >> manufacturer >> dummy >> color;
                this->createCab(idTaxi, typeOfTaxi, manufacturer, color);
                break;
            }
                // this mission is for printing the current point of specific driver
            case 4: {
                int idToGet;
                cin >> idToGet;
                Driver *driverCurrentPoint = this->getTaxiCenter()->getDriverById(idToGet);
                Node *currentPoint = driverCurrentPoint->getCurrentPoint();
                currentPoint->getPoint().printPoint();
                break;
            }
                //this mission is fpr make the move of the drivers that holds a trip
            case 6: {
                this->getTaxiCenter()->connectDriversToTrips();
                this->getTaxiCenter()->startDriving();
                break;
            }
            //this mission increase the time by one
            case 9: {
                time++;
                break;
            }
        }
        //if the user press 7 the game will end
    }while(mission!=7);
    return;
}


