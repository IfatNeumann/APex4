#ifndef APEX2_CAB_H
#define APEX2_CAB_H
#include <iostream>
#include "Color.h"
#include "Manufacturer.h"

class Cab {
protected:
    int id;
    Manufacturer manufacturer;
    Color color;
    float tariffCoefficient;
    float totalKMPassed;

    public:
    /**
     * Constructor.
     * Gets its members' information from the Cab's constructor.
     * @param cabId the id of this cab
     * @param standardOrLuxuryCab the type pf this cab
     * @param cabManufacturer the manufacturer of this cab
     * @param cabColor the color of this cab
     */
    Cab(int cabId,int standardOrLuxuryCab,Manufacturer cabManufacturer, Color cabColor);
    /**
     * Destructor.
     */
    ~Cab();
    /**
     * This function return the cab's id.
     * @return id - variable from type int
     */
    int getId();
    /**
     * This function return the cab's total kilometers passed.
     * @return totalKMPassed- variable from type float
     */
    float getTotalKmPassed();
    /**
     * This function return the cab's manufacturer.
     * @return manufacturer-variable from type Manufacturer.
     */
    Manufacturer getManufacturer();
    /**
     * This function return the cab's color.
     * @return color - variable from type Color.
     */
    Color getColor();
    /**
     * This function return the cab's tariff coefficient.
     * @return tariffCoefficient - variable from type float
     */
    float getTariffCoefficient();
    /**
     *
     * @param meters
     */
    virtual void setKmPassed(float meters) = 0;


};


#endif //APEX2_CAB_H
