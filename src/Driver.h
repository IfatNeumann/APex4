/**
 *
 */

#ifndef APEX1_DRIVER_H
#define APEX1_DRIVER_H

#include "Cab.h"
#include "MaritalStatus.h"
#include "Passenger.h"
#include "TripInfo.h"
#include "Node.h"
#include <vector>
#include <cstdlib>
#include <boost/serialization/vector.hpp>
using namespace std;

class Driver{
private:
    int id;
    int age;
    MaritalStatus martialSta;
    int yrsOfExp;
    double avgStsfc;
    int taxiId;
    Cab* txCabInfo;
    int totalCustomersNum;
    vector<Passenger*> currentPassen;
    TripInfo* myTripInfo;
    Node* currentPoint;
    bool ifAvailable;
    int clientDescriptor;
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & id;
        ar & age;
        ar & martialSta;
        ar & yrsOfExp;
        ar & avgStsfc;
        ar & taxiId;
        ar & txCabInfo;
        ar & totalCustomersNum;
        ar & currentPassen;
        ar & myTripInfo;
        ar & currentPoint;
        ar & ifAvailable;
    }
public:
    /**
     * Constructor.
     * Gets the driver's id, Age, MaritalStatus, Years of Experience,And cab information -
     * And puts them in its members.
 * @param id the id of the driver
 * @param age the age of the driver
 * @param martialSta the martial status of the driver
 * @param yrsOfExp number of years of experience
 * @param taxiId the id of the cab object that belongs to this driver
 */
    Driver(int id, int age, MaritalStatus martialSta, int yrsOfExp, int taxiId);
    /**
     * Constructor.
     */
    Driver();
    /**
     * Destructor.
     */
    ~Driver();
    /**
     * This function returns the vector of the current passengers.
     * @return vector that content object of the current passengers ride
     */
    vector<Passenger*> getListOfPassen();
    /**
     * This function returns the driver's id.
     * @return id- variable form type int
     */
    int getId();
    /**
     * This function returns the driver's age.
     * @return age- variable form type int
     */
    int getAge();
    /**
     * This function returns the driver's martial status.
     * @return martialSta- variable from type MartialStatus
     */
    MaritalStatus getMartialSta();
    /**
     * This function returns the driver's year of experience.
     * @return yrsOfExp- variable from type int
     */
    int getYrsOfExp();
    /**
     * This function returns the driver's average of passengers satisfaction.
     * @return avgStsfc- variable from type double
     */
    double getAvgStsfc();
    /**
     * This function return the id of the cab object that belong to this driver.
     * @return taxiId - the taxi's id
     */
    int getTaxiId();
    /**
     * This function return the total number of customers that got a ride with this driver.
     * @return totalCustomersNum- variable from type int
     */
    int getCustomersNum();
    /**
     * This function return a point to a 'TripInfo' object that belong (for now) to this driver.
     * @return pointer to 'TripInfo'
     */
    TripInfo* getMyTripInfo();
    /**
     * This function return the point that the driver have a place there right now.
     * @return pointer to Node object
     */
    Node* getCurrentPoint();
    Cab* getTxCabInfo();
    /**
     * This function return true or false accordingly the availability of the driver to get a new ride.
     * @return true or false
     */
    bool getIfAvailable();
    /**
     * This function will use us for the next exercises, it will get and calculate the average of the passengers
     * satisfaction.
     * @param avgStsfc
     */
    void setAvgStsfc();
    /**
     * This function sum the number of the passengers that toke a ride with this driver and set the new sum.
     */
    void setTotalCustomersNum();
    /**
     * This function set the vector of the current passengers.
     * @param currentPassnegers vector of passengers objects
     */
    void setCurrentPassen(vector<Passenger*> currentPassnegers);
    /**
     * This function set the current trip of the driver.
     * @param tripInfo object fron type 'TripInfo' which mean the ride that the driver should do
     */
    void setMyTripInfo(TripInfo* tripInfo);
    /**
     * This function change the driver's current point.
     * @param current a pointer to the new current Node
     */
    void setCurrentPoint(Node* current);
    /**
     * This function change the diver's availability.
     * @param availableOrNot boolean variable- true or false
     */
    void setIfAvailable(bool availableOrNot);
    /**
     * This function adds a new passenger to the driver's 'current passengers' list.
     * @param p a pointer to a Passenger object
     */
    void addPassn(Passenger* passenger);
    /**
     * This function clear the list of the passengers
     */
    void clearList();
    void setTxCabInfo(Cab* cab);
};
#endif //APEX1_DRIVER_H
