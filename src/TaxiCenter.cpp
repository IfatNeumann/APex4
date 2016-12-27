#include "TaxiCenter.h"

TaxiCenter::TaxiCenter() {
    this->driversList;
    this->tripsList;
}

TaxiCenter::~TaxiCenter() {
    for (int i = 0; i < driversList.size(); ++i) {
        delete driversList[i];
    }
    for (int i = 0; i < tripsList.size(); ++i) {
        if (tripsList[i] != NULL) {
            delete tripsList[i];
        }
    }
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
          if (this->tripsList[indexOfTrip]->getStartingP()->getPoint().getX()==this->driversList[i]->getCurrentPoint()->
                  getPoint().getX()&&this->tripsList[indexOfTrip]->getStartingP()->getPoint().getY()==
                                                           this->driversList[i]->getCurrentPoint()->getPoint().getY()
              &&this->driversList[i]->getifAvailable()==true){
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

void TaxiCenter::connectDriversToTrips(){
    for(int i=0;i<tripsList.size();i++) {
        if (this->tripsList[i] != NULL) {
            int indexOfDriver = srcClosestTaxiDriver(i);
            if (indexOfDriver != -1) {
                this->driversList[indexOfDriver]->setMyTripInfo(this->tripsList[i]);
                updateDriverPassengers(this->driversList[indexOfDriver],
                                       this->tripsList[i]->getStartingP(),
                                       this->tripsList[i]->getEndingP(),
                                       this->tripsList[i]->getNumOfPassen());
                tripsList[i]->setHaveDriver(true);
            }
        }
    }
}

    void TaxiCenter::startDriving(){
        for(int i=0;i<this->driversList.size();i++){
            if(driversList[i]->getMyTripInfo()!=NULL) {
                driversList[i]->setCurrentPoint(driversList[i]->getMyTripInfo()->getEndingP());
                driversList[i]->setIfAvailable(true);
                driversList[i]->setMyTripInfo(NULL);
            }
        }
        for(int i=0;i<this->tripsList.size();i++){
            if(tripsList[i]!=NULL&&tripsList[i]->getHaveDriver()==true){
                delete(tripsList[i]);
                tripsList[i] = NULL;
            }
        }
    }
