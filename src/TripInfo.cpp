#include "TripInfo.h"

TripInfo::TripInfo(){}
TripInfo::TripInfo(int rideId, Node* startingP, Node* endingP, int numOfPassen,double tariff, int timeOfStart)
{
    this->rideId = rideId;
    this->totalMetersPassed = 0;
    this->startingP = startingP;
    this->endingP = endingP;
    this->numOfPassen = numOfPassen;
    this->tariff = tariff;
    this->haveDriver = false;
    this->timeOfStart = timeOfStart;
    this->tripJustStart = true;
    this->myWay;
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
void TripInfo::setTripJustStart(bool startOrNot) {
    this->tripJustStart=startOrNot;
}
void TripInfo::setMyWay(stack<Point> tripWay) {
    this->myWay = tripWay;

    myWay.pop();
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

int TripInfo::getTimeOfStart(){
    return this->timeOfStart;
}
bool TripInfo::getTripJustStart() {
    return this->tripJustStart;
}
Point TripInfo::getNextPoint(int stanOrLux){
    int i = 0;
    Point current;
    //case that the cab is luxury but we need less than two steps to get to the trip's end point
    if(stanOrLux==2 && this->myWay.top().isEqualTo(this->endingP->getPoint())){
        stanOrLux = 1;
    }
    while(i<stanOrLux) {
        current = this->myWay.top();
        this->myWay.pop();
        i++;
    }
    return current;
}

