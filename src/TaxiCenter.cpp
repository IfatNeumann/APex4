#include "TaxiCenter.h"

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


int TaxiCenter::srcClosestTaxiDriver(int indexOfTrip) {
     for (int i = 0; i <driversList.size();i++) {
          if ((this->tripsList[indexOfTrip]->getStartingP()->getPoint().isEqualTo
                  (this->driversList[i]->getCurrentPoint()->getPoint()))&&
                  (this->driversList[i]->getIfAvailable())){
              this->driversList[i]->setIfAvailable(false);
              return i;
          }
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

void TaxiCenter::connectDriversToTrips(int indexOfTrip){
            int indexOfDriver = srcClosestTaxiDriver(indexOfTrip);
            if (indexOfDriver != -1) {
                this->driversList[indexOfDriver]->setMyTripInfo(this->tripsList[indexOfTrip]);
                updateDriverPassengers(this->driversList[indexOfDriver],
                                       this->tripsList[indexOfTrip]->getStartingP(),
                                       this->tripsList[indexOfTrip]->getEndingP(),
                                       this->tripsList[indexOfTrip]->getNumOfPassen());
                tripsList[indexOfTrip]->setHaveDriver(true);
                tripsList[indexOfTrip]->setMyWay(this->myBFS->bfs(tripsList[indexOfTrip]->getStartingP(),
                                                                  tripsList[indexOfTrip]->getEndingP()));
            }
        }



    void TaxiCenter::startDriving(){
        for(int i=0;i<this->driversList.size();i++){
            if(driversList[i]->getMyTripInfo()!=NULL&&driversList[i]->getMyTripInfo()->getTripJustStart()==false) {
                driversList[i]->setCurrentPoint(getTheNextNode(i));
            }
            if(driversList[i]->getMyTripInfo()->getTripJustStart()){
                driversList[i]->getMyTripInfo()->setTripJustStart(false);
            }
            if(driversList[i]->getCurrentPoint()==driversList[i]->getMyTripInfo()->getEndingP()){
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
