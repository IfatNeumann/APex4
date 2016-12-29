/**
 * Class TripInfo.
 * This class has all the trip information: Ride id, Number of Km passed, starting point,
 * Ending point, number of passengers and Tariff.
 */

#ifndef APEX2_TRIPINFO_H
#define APEX2_TRIPINFO_H

#include "Point.h"
#include "Node.h"

class TripInfo {
private:
    int rideId;
    float totalMetersPassed;
    Node *startingP;
    Node *endingP;
    int numOfPassen;
    double tariff;
    bool haveDriver;
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & rideId;
        ar & totalMetersPassed;
        ar & startingP;
        ar & endingP;
        ar & numOfPassen;
        ar & tariff;
        ar & haveDriver;
    }

public:
    TripInfo();
 /**
  * Constructor.
  * @param rideId the id of this ride (trip)
  * @param startingP the trip's start point
  * @param endingP the trip's end point
  * @param numOfPassen the number of the passengers in this trip
  * @param tariff the tariff to this trip
  */
    TripInfo(int rideId, Node *startingP, Node *endingP, int numOfPassen, double tariff);

    /**
     * Destructor.
     */
    ~TripInfo();

    /**
     * This function sets the ride's id.
     * @param rideId variable from int type that represent the id of the ride
     */
    void setRideId(int rideId);

    /**
     * This function sets the ride's meters passed.
     * @param meters the meters that we want to set
     */
    void setMetersPassed(float meters);

    /**
     * This function sets the ride's starting point.
     * @param start pointer to the point that we want to set
     */
    void setStartingP(Node *start);

    /**
     * This function sets the ride's ending point.
     * @param end pointer to the point that we want to set
     */
    void setEndingP(Node *end);

    /**
     * This function sets the ride's number of passengers.
     * @param setNumOfPassen the number of the passengers that we want to set
     */
    void setNumOfPassen(int setNumOfPassen);

    /**
     * This function sets the ride's tariff.
     * @param tariff the tariff that we want to set.
     */
    void setTariff(float tariff);
    /**
     * This function set the status of the trip- if it already got a driver or not
     * @param haveOrNot variable from type boolean
     */
    void setHaveDriver(bool haveOrNot);
    /**
     * This function returns the ride's id.
     * @return variable from type int
     */
    int getRideId();

    /**
     * his function returns the ride's meters passed.
     * @return variable from type float
     */
    float getTotalMetersPassed();

    /**
     * This function returns the ride's starting point.
     * @return variable from type pointer to point
     */
    Node *getStartingP();

    /**
     * This function returns the ride's ending point.
     * @return variable from type pointer to point
     */
    Node *getEndingP();

    /**
     * This function returns the ride's number of passengers.
     * @return variable from type int
     */
    int getNumOfPassen();

    /**
     * This function returns the ride's tariff.
     * @return variable from type float
     */
    float getTariff();
    /**
     * This function return the boolean variable -'haveDriver'
     * @return true or false
     */
    bool getHaveDriver();
};


#endif //APEX2_TRIPINFO_H
