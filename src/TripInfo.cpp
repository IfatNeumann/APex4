#include "TripInfo.h"
TripInfo::TripInfo(){}
TripInfo::TripInfo(int rideId, Node* startingP, Node* endingP, int numOfPassen,double tariff)
{
    this->rideId = rideId;
    this->totalMetersPassed = 0;
    this->startingP = startingP;
    this->endingP = endingP;
    this->numOfPassen = numOfPassen;
    this->tariff = tariff;
    this->haveDriver = false;
}

TripInfo::~TripInfo() {
}

void TripInfo::setRideId(int rideId){
    this->rideId = rideId;
}

void TripInfo::setMetersPassed(float meters){
    this->totalMetersPassed = meters;
}

void TripInfo::setStartingP(Node *start){
    this->startingP = start;
}

void TripInfo::setEndingP(Node *end){
    this->endingP = end;
}

void TripInfo::setNumOfPassen(int numOfPassen){
    this->numOfPassen = numOfPassen;
}

void TripInfo::setTariff(float tariff){
    this->tariff = tariff;
}
void TripInfo::setHaveDriver(bool haveOrNot){
    this->haveDriver = haveOrNot;
}
int TripInfo::getRideId(){
    return this->rideId;
}

float TripInfo::getTotalMetersPassed(){
    this->totalMetersPassed;
}

Node* TripInfo::getStartingP(){
    return this->startingP;
 }

Node* TripInfo::getEndingP(){
    return this->endingP;
}

int TripInfo::getNumOfPassen(){
    return this->numOfPassen;
}

float TripInfo::getTariff(){
    return this->tariff;
}

bool TripInfo::getHaveDriver(){
    return this->haveDriver;
}

