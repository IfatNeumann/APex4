#include "MainFlow.h"
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "Client.h"
#include "Driver.h"
#include "../sockets/Tcp.h"
int mission;

class ThreadClient{
public:
    TaxiCenter* taxiCenter;
    Tcp* sock;
    MainFlow* flow;
    ThreadClient(Tcp* s, MainFlow* f){
        this->sock = s;
        this->flow = f;
    }
    ~ThreadClient(){}
};

//
// This will handle connection for each client
//
void *connectionHandler(void *socket_desc) {
    ThreadClient* handler = (ThreadClient*)socket_desc;
    char buffer[4096];
    int clientDescriptor = handler->sock->acceptOneClient();
    int dataSize = handler->sock->reciveData(buffer, 4096,clientDescriptor);
    Driver *driver;
    boost::iostreams::basic_array_source<char> device(buffer, dataSize);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> driver;
    driver->setCurrentPoint(handler->flow->getGrid()->getNode(Point(0,0)));
    Node* currentPoint=driver->getCurrentPoint();
    //find the taxi
    Cab* taxi = handler->flow->getCab(driver->getTaxiId());

    //send the taxi case number
    handler->sock->sendData("2",clientDescriptor);
    //send the taxi
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << taxi;
    s.flush();
    handler->sock->sendData(serial_str,clientDescriptor);
    //serialize and send current point
    std::string serial_str3;
    boost::iostreams::back_insert_device<std::string> inserter3(serial_str3);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s4(inserter3);
    boost::archive::binary_oarchive oc(s4);
    oc << currentPoint;
    s4.flush();
    handler->sock->sendData(serial_str3,clientDescriptor);
    //receive driver *with* his cab object
    dataSize = handler->sock->reciveData(buffer,4096,clientDescriptor);
    boost::iostreams::basic_array_source<char> device6(buffer,dataSize);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s7(device6);
    boost::archive::binary_iarchive ih(s7);
    delete driver;
    ih >> driver;
    driver->setClientDescriptor(clientDescriptor);
    handler->taxiCenter->addDriver(driver);

    pthread_exit(socket_desc);
}

MainFlow::MainFlow(){
    this->myTaxiCenter = new TaxiCenter();
    this->grid;
    this->cabsVector;
    this->threads;
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
    this->myTaxiCenter->setMyGrid(this->grid);
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

int MainFlow::checkIfTimeToTrip(int time){
    for(int i=0; i<this->myTaxiCenter->getTripsVector().size();i++) {
        if(this->myTaxiCenter->getTripsVector().at(i)!=NULL&&
                this->myTaxiCenter->getTripsVector().at(i)->getTimeOfStart()==time&&
                this->myTaxiCenter->getTripsVector().at(i)->getHaveDriver()== false){
            this->myTaxiCenter->connectDriversToTrips(i);
            return i;
        }
    }
    return -1;
}

void MainFlow::mainFlow(int portNum){
    int time=0;
    int gridXAxe,gridYAxe,numOfObstacles;
    int xPoint,yPoint;
    char dummy;
    char buffer[4096];
    Tcp* socket= new Tcp(true,portNum);
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
                for(int i = 0; i < numOfDrivers; i++){
                    //receive the driver
                    ThreadClient* threadHandler = new ThreadClient(socket, this);
                    pthread_create(&threads[i], NULL, connectionHandler, (void*)threadHandler);
                }
                break;
            }
                //this mission is for creating and adding a new trip to the game
            case 2: {
                int tripId, xStartPoint, yStartPoint, xEndPoint, yEndPoint, numOfpassn,timeOfStart;
                double tariff;
                //initialize the nodes' 'visited' values
                this->getGrid()->initializeBeforeTrip();
                cin >> tripId >> dummy >> xStartPoint >> dummy >> yStartPoint >> dummy >>
                    xEndPoint >> dummy >> yEndPoint >>
                    dummy >> numOfpassn >> dummy >> tariff >> dummy >> timeOfStart;
                this->createTripInfo(tripId, xStartPoint, yStartPoint, xEndPoint, yEndPoint,
                                     numOfpassn, tariff, timeOfStart);
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
            //this mission increase the time by one
            case 9: {
                time++;
                int thereIsTrip = checkIfTimeToTrip(time);
                this->getTaxiCenter()->startDriving();
                Driver* driver = this->myTaxiCenter->getDriverById(0);
                //int thereIsTrip = checkIfTimeToTrip(time);
                if(thereIsTrip!=-1){
                    //find the trip info
                    TripInfo* tripInfo = this->myTaxiCenter->getTripsVector().at(thereIsTrip);
                    //sent the tripInfo case number
                    socket->sendData("3",driver->getClientDescriptor());
                    //send the tripInfo
                    std::string serial_str2;
                    boost::iostreams::back_insert_device<std::string> inserter2(serial_str2);
                    boost::iostreams::stream<boost::iostreams::back_insert_device
                            <std::string> > s3(inserter2);
                    boost::archive::binary_oarchive ob(s3);
                    ob << tripInfo;
                    s3.flush();
                    socket->sendData(serial_str2,driver->getClientDescriptor());

                    //find destPoint
                    Node* destPoint = this->myTaxiCenter->getTripsVector().at(thereIsTrip)
                            ->getEndingP();
                    //sent the destination point case number
                    socket->sendData("4",driver->getClientDescriptor());
                    //send the destination point
                    std::string serial_str3;
                    boost::iostreams::back_insert_device<std::string> inserter3(serial_str3);
                    boost::iostreams::stream<boost::iostreams::back_insert_device
                            <std::string> > s4(inserter3);
                    boost::archive::binary_oarchive oc(s4);
                    oc << destPoint;
                    s4.flush();
                    socket->sendData(serial_str3,driver->getClientDescriptor());

                }
                //sent the new location case number
                socket->sendData("5",driver->getClientDescriptor());
                //send new location (Node*)
                Node* newLocation = this->myTaxiCenter->getDriversVector().at(0)->
                        getCurrentPoint();
                std::string serial_str4;
                boost::iostreams::back_insert_device<std::string> inserter4(serial_str4);
                boost::iostreams::stream<boost::iostreams::back_insert_device
                        <std::string> > s5(inserter4);
                boost::archive::binary_oarchive od(s5);
                od << newLocation;
                s5.flush();
                socket->sendData(serial_str4,driver->getClientDescriptor());
                break;
            }
        }
        //if the user press 7 the game will end
    }while(mission!=7);
    Driver* driver = this->myTaxiCenter->getDriverById(0);
    //sent the delete case number
    socket->sendData("7",driver->getClientDescriptor());
}


