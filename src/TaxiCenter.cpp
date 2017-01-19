#include "TaxiCenter.h"
class ThreadBFS{
public:
    TripInfo* trip;
    BFS* bfs;
    pthread_mutex_t bfs_locker;
    ThreadBFS(BFS* b, TripInfo* t){
        this->bfs = b;
        this->trip =t;
        //pthread_mutex_init(&this->bfs_locker, 0);
    }
    ~ThreadBFS(){}
};

void *BFSThandler(void *bfs_desc) {
    ThreadBFS* handler = (ThreadBFS*)bfs_desc;
    pthread_mutex_lock(&handler->bfs_locker);
    cout<<"setting trip info way"<<endl;
    handler->trip->setMyWay(handler->bfs->bfs(handler->trip->getStartingP(),
                                              handler->trip->getEndingP()));
    pthread_mutex_unlock(&handler->bfs_locker);
    cout<<"bye bye thread"<<endl;
    handler->trip->setDoneToCal(true);
    pthread_exit(NULL);
}

TaxiCenter::TaxiCenter() {
    this->driversList;
    this->tripsList;
    this->myGrid = NULL;
    this->myBFS = NULL;
}

TaxiCenter::~TaxiCenter() {
    delete(myBFS);
    for (int i = 0; i < driversList.size(); ++i) {
        delete driversList[i];
    }
    for (int i = 0; i < tripsList.size(); ++i) {
        if (tripsList[i] != NULL) {
            delete tripsList[i];
        }
    }
}

void TaxiCenter::setMyGrid(Grid* gameGrid) {
    this->myGrid = gameGrid;
    setMyBFS();
}
void TaxiCenter::setMyBFS() {
    this->myBFS = new BFS(this->myGrid);
}
vector<Driver*> TaxiCenter::getDriversVector(){
    return this->driversList;
}

vector<TripInfo*> TaxiCenter::getTripsVector(){
    return this->tripsList;
}

void TaxiCenter::addDriver(Driver* newDriver) {
    driversList.push_back(newDriver);
}

void TaxiCenter::addTrip(TripInfo* newTrip) {
    tripsList.push_back(newTrip);
}
Driver* TaxiCenter::getDriverById(int id){
    for(int i=0;i<this->driversList.size();i++){
        if(this->driversList[i]->getId()==id){
            return this->driversList[i];
        }
    }
}


void TaxiCenter::answerPhone(Point* source, Point* dest, int numOfPassengers){
}


int TaxiCenter::srcClosestTaxiDriver(int indexOfTrip, int i) {
    if ((this->tripsList[indexOfTrip]->getStartingP()->getPoint().isEqualTo
            (this->driversList[i]->getCurrentPoint()->getPoint()))&&
        (this->driversList[i]->getIfAvailable())){
        this->driversList[i]->setIfAvailable(false);
        return i;
    }
    return -1;
}


void TaxiCenter::updateDriverPassengers(Driver* closestTaxi, Node* costmSource, Node* costmDest,int numOfPassen) {
    vector<Passenger*> currentPassen;
    for(int i=0;i<numOfPassen;i++) {
        currentPassen.push_back(new Passenger(costmSource, costmDest));
    }
    closestTaxi->setCurrentPassen(currentPassen);
    closestTaxi->setTotalCustomersNum();
}

void TaxiCenter::connectDriversToTrips(int indexOfTrip,int driverId){
    int indexOfDriver = srcClosestTaxiDriver(indexOfTrip,driverId);
    if (indexOfDriver != -1) {
        this->driversList[indexOfDriver]->setMyTripInfo(this->tripsList[indexOfTrip]);
        updateDriverPassengers(this->driversList[indexOfDriver],
                               this->tripsList[indexOfTrip]->getStartingP(),
                               this->tripsList[indexOfTrip]->getEndingP(),
                               this->tripsList[indexOfTrip]->getNumOfPassen());
        tripsList[indexOfTrip]->setHaveDriver(true);
        tripsList[indexOfTrip]->setTripJustStart(true);
        ThreadBFS *newBFSThread = new ThreadBFS(this->myBFS,tripsList[indexOfTrip]);
        pthread_t tBFS;
        tripsList[indexOfTrip]->setThread(tBFS);
        int status=pthread_create(&tBFS,NULL,BFSThandler,newBFSThread);
        if(status!=0){
            cout<<"Didn't succeed to create bfs thread"<<endl;
        }
        else {
            cout << "create bfs thread" << endl;
        }
    }
}



void TaxiCenter::startDriving(int i){
    int tripIndex;
    if(driversList[i]->getMyTripInfo()!=NULL) {
        if (driversList[i]->getMyTripInfo()->getTripJustStart() == false) {
            //waiting for thread that doesn't finish to calculate the bfs yet
            if(!driversList[i]->getMyTripInfo()->getDoneToCal()){
                pthread_join(driversList[i]->getMyTripInfo()->getThread(),NULL);
            }
            driversList[i]->setCurrentPoint(getTheNextNode(i));
        }
        if (driversList[i]->getMyTripInfo()->getTripJustStart() == true) {
            driversList[i]->getMyTripInfo()->setTripJustStart(false);
        }
        if (driversList[i]->getCurrentPoint() == driversList[i]->getMyTripInfo()->getEndingP()) {
            deleteTripThatEnd(i);
            driversList[i]->setIfAvailable(true);
            driversList[i]->setMyTripInfo(NULL);
        }
    }
}


void TaxiCenter::deleteTripThatEnd(int indexOfTrip){
    if(tripsList[indexOfTrip]!=NULL&&tripsList[indexOfTrip]->getHaveDriver()==true) {
        delete (tripsList[indexOfTrip]);
        tripsList[indexOfTrip] = NULL;
    }
}

Node* TaxiCenter::getTheNextNode(int indexOfDriver){
    Point current=driversList[indexOfDriver]->getMyTripInfo()->getNextPoint(driversList[indexOfDriver]->getTxCabInfo()->
            getTariffCoefficient());
    return this->myGrid->getNode(current);
}