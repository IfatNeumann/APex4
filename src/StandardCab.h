/**
 *
 * Class StandardCab.
 * This class inherits from 'Cab' class.
 * This class has its own 'setKmPassed' function.
*/

#ifndef APEX2_STANDARDCAB_H
#define APEX2_STANDARDCAB_H

#include "Cab.h"

class StandardCab : public Cab {
    friend class boost::serialization::access;

    template <class Archive>
            void serialize(Archive &ar, const unsigned int version){
        ar & boost::serialization::base_object<Cab>(*this);
    }
public:
    /**
     * Constructor.
     * Gets its members' information from the Cab's constructor.
     * @param cabId the id of this cab
     * @param standardOrLuxuryCab the type pf this cab
     * @param cabManufacturer the manufacturer of this cab
     * @param cabColor the color of this cab
     */
    StandardCab(int cabId,int standardOrLuxuryCab,Manufacturer cabManufacturer, Color cabColor);
    /**
     * This function sets the number of passed Km. This function is different between the two cabs because
     * they move in different speed.
     * @param meters
     */
    void setKmPassed(float meters);
};


#endif //APEX2_STANDARDCAB_H
