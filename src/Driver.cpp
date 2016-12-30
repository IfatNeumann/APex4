/**
 * Class Driver.
 * This class is responsible for the driver's data, Which contains:
 * Id, Age, MaritalStatus, Years of Experience, Average satisfaction, Cab information,
 * Total number of customers , A vector of the current passengers,
 * Trip information, And current point.
 */
#include "Driver.h"
Driver::Driver(){}
Driver::Driver(int id, int age, MaritalStatus martialSta, int yrsOfExp, Cab* texiInfo,Node* currentPoint)
{
    this->id=id;
    this->age=age;
    this->martialSta=martialSta;
    this->yrsOfExp=yrsOfExp;
    this->avgStsfc=0;
    this->txCabInfo=texiInfo;
    this->totalCustomersNum=0;
    this->currentPassen;
    this->myTripInfo=NULL;
    this->currentPoint=currentPoint;
    this->ifAvailable = true;
}

Driver::Driver(int id, int age, MaritalStatus martialSta, int yrsOfExp, int taxiId)
{
    this->id=id;
    this->age=age;
    this->martialSta=martialSta;
    this->yrsOfExp=yrsOfExp;
    this->avgStsfc=0;
    this->taxiId=taxiId;
    this->txCabInfo=NULL;
    this->totalCustomersNum=0;
    this->currentPassen;
    this->myTripInfo=NULL;
    this->currentPoint;
    this->ifAvailable = true;
}

/**
 * Destructor.
 */
Driver::~Driver() {
 for(int i=0;i<currentPassen.size();++i){
        delete currentPassen[i];
    }
}
vector<Passenger*> Driver::getListOfPassen(){
    return this->currentPassen;
}

int Driver::getId() {
    return this->id;
}

int Driver::getAge() {
    return this->age;
}

MaritalStatus Driver::getMartialSta() {
    return this->martialSta;
}

int Driver::getYrsOfExp(){
    return this->yrsOfExp;
}
double Driver::getAvgStsfc(){
    return this->avgStsfc;
}
int Driver::getTaxiId(){
    return this->taxiId;
}
int Driver::getCustomersNum(){
    return this->totalCustomersNum;
}
TripInfo* Driver::getMyTripInfo(){
    return this->myTripInfo;
}
Node* Driver::getCurrentPoint() {
    return currentPoint;
}
bool Driver::getifAvailable(){
    return this->ifAvailable;
}
void Driver::setAvgStsfc() {
}
void Driver::setTotalCustomersNum() {
    this->totalCustomersNum+=this->currentPassen.size();
}
void Driver::setCurrentPassen(vector<Passenger*> currentPassnegers){
    clearList();
    this->currentPassen = currentPassnegers;
}
void Driver::setMyTripInfo(TripInfo* tripInfo){
    this->myTripInfo =tripInfo;
    }
void Driver::setCurrentPoint(Node* current){
    this->currentPoint=current;
}
void Driver::setIfAvailable(bool availableOrNot){
    this->ifAvailable=availableOrNot;
}
void Driver::addPassn(Passenger* passenger){
    this->currentPassen.push_back(passenger);
}
void Driver::clearList(){
    for(int i=0;i<currentPassen.size();++i){
        delete currentPassen[i];
        currentPassen[i]=NULL;
    }
}


void Driver::setTaxi(Cab* cab){
    this->txCabInfo=cab;
}