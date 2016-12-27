#include "MainFlow.h"

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

void MainFlow::createDriver(int id,int age,char status,int experience,int texiId){
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
                                   int numOfpassn, double tariff){
    TripInfo* newTrip = new TripInfo(tripId,grid->getNode(Point(xStartPoint,yStartPoint)),
                                     grid->getNode(Point(xEndPoint,yEndPoint)),numOfpassn,tariff);
    this->myTaxiCenter->addTrip(newTrip);
}

void MainFlow::createGrid(int gridX,int gridY){
    this->grid = new Grid(gridX,gridY);
    return;
}
Grid* MainFlow::getGrid(){
    return this->grid;
}

void mainflow(){
    int gridXAxe,gridYAxe,numOfObstacles;
    int xPoint,yPoint;
    char dummy;
    int mission;
    MainFlow *myMainFlow = new MainFlow();
    //entered the size of the grid (map)
    cin >> gridXAxe >> gridYAxe;
    myMainFlow->createGrid(gridXAxe,gridYAxe);
    //entered the numbers of the obstacles that will be at the map
    cin >> numOfObstacles;
    //add the obstacles to the map
    while(numOfObstacles>0){
        cin >> xPoint >> dummy >> yPoint;
        myMainFlow->getGrid()->getNode(Point(xPoint,yPoint))->setIsObstacle();
        numOfObstacles--;
    }

    do{
        cin>>mission;
        switch (mission) {
            //this mission is for creating and adding a new cab to the game
            case 1: {
                int id, age, experience, texiId;
                char status;
                cin >> id >> dummy >> age >> dummy >> status >> dummy >> experience >> dummy >> texiId;
                myMainFlow->createDriver(id, age, status, experience, texiId);
                break;
            }
                //this mission is for creating and adding a new trip to the game
            case 2: {
                int tripId, xStartPoint, yStartPoint, xEndPoint, yEndPoint, numOfpassn;
                double tariff;
                cin >> tripId >> dummy >> xStartPoint >> dummy >> yStartPoint >> dummy >> xEndPoint >> dummy >> yEndPoint >>
                    dummy >> numOfpassn >> dummy >> tariff;
                myMainFlow->createTripInfo(tripId, xStartPoint, yStartPoint, xEndPoint, yEndPoint, numOfpassn, tariff);
                break;
            }
                //this mission is for creating and adding a new driver to the game
            case 3: {
                int idTaxi;
                int typeOfTaxi;
                char manufacturer, color;
                cin >> idTaxi >> dummy >> typeOfTaxi >> dummy >> manufacturer >> dummy >> color;
                myMainFlow->createCab(idTaxi, typeOfTaxi, manufacturer, color);
                break;
            }
                // this mission is for printing the current point of specific driver
            case 4: {
                int idToGet;
                cin >> idToGet;
                Driver *driverCurrentPoint = myMainFlow->getTaxiCenter()->getDriverById(idToGet);
                Node *currentPoint = driverCurrentPoint->getCurrentPoint();
                currentPoint->getPoint().printPoint();
                break;
            }
                //this mission is fpr make the move of the drivers that holds a trip
            case 6: {
                myMainFlow->getTaxiCenter()->connectDriversToTrips();
                myMainFlow->getTaxiCenter()->startDriving();
                break;
            }
        }
        //if the user press 7 the game will end
    }while(mission!=7);
    delete (myMainFlow);
    return
}


