#include "LuxuryCab.h"

LuxuryCab::LuxuryCab(int cabId,int standardOrLuxuryCab,Manufacturer cabManufacturer, Color cabColor) :
        Cab(cabId,standardOrLuxuryCab,cabManufacturer,cabColor)  {}

void LuxuryCab::setKmPassed(float meters){
    totalKMPassed = meters;
}
