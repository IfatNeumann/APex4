#include "StandardCab.h"

StandardCab::StandardCab(int cabId,int standardOrLuxuryCab,Manufacturer cabManufacturer, Color cabColor) :
        Cab(cabId,standardOrLuxuryCab,cabManufacturer,cabColor) {}

void StandardCab::setKmPassed(float meters){
    totalKMPassed = meters;
}
