#include "Cab.h"
Cab::Cab(){}
Cab::Cab(int cabId,int standardOrLuxuryCab,Manufacturer cabManufacturer, Color cabColor){
    id = cabId;
    totalKMPassed = 0;
    manufacturer = cabManufacturer;
    color = cabColor;
    if(standardOrLuxuryCab==1){
        tariffCoefficient =1;
    }
    else{
        tariffCoefficient =2;
    }
}

Cab::~Cab() {

}

int Cab::getId(){
    return id;
}

float Cab::getTotalKmPassed(){
    return totalKMPassed;
}

Manufacturer Cab::getManufacturer(){
    return manufacturer;
}

Color Cab::getColor(){
    return color;
}

float Cab::getTariffCoefficient(){
    return tariffCoefficient;
}
