/**
 * Class TaxiCenter.
 * This class is a taxi center - it manage all the drivers,trips and passengers- it connects drivers to passengers,
 * connects drivers to trips and make the drivers move.
 * Its member is a vector 'driversList' that contains all the drivers in the program, and vector 'tripList'
 * that contains all the trips in the program.
 */

#ifndef APEX2_TAXICENTER_H
#define APEX2_TAXICENTER_H

#include "Driver.h"
#include "Point.h"
#include <vector>

using namespace std;

class TaxiCenter {
private:
    vector <Driver*> driversList;
    vector <TripInfo*> tripsList;
    Grid* myGrid;
    BFS* myBFS;
public:
    /**
     * constructor.
     */
    TaxiCenter();

    /**
     * Destructor.
     */
    ~TaxiCenter();
    void setMyGrid(Grid* gameGrid);
    void setMyBFS();
    /**
     * This function returns the drivers vector.
     * @return vector of the drivers objects.
     */
    vector<Driver*> getDriversVector();

    /**
     * This function returns the trips vector.
     * @return vector of the trips objects.
     */
    vector<TripInfo*> getTripsVector();

    /**
     * This function adds a new driver to the drivers vector.
     * @param newDriver the new object driver that we want to add to the list
     */
    void addDriver(Driver* newDriver);

    /**
     * This function adds a new trip to the trips vector.
     * @param newTrip the new object trip that we want to add to the list
     */
    void addTrip(TripInfo* newTrip);

    /**
     * This function returns a driver based on a given id.
     * @param id the id of the number that we want to get
     * @return the object of the Driver with the id that we want
     */
    Driver* getDriverById(int id);

    /**
     * This function will be use in the next exerices- This function
     * can gat a call phone from passenger and get an information
     * about a trip that he want to do
     * @param source the passenger's ask source point
     * @param dest the passenger's ask source point
     * @param passengers the number of the passengers that want to go to the ride
     */
    void answerPhone(Point* source, Point* dest, int numOfPassengers);

    /**
     * This function search the driver who is closest the most to the start point of the trip
     * and returns his index in the drivers vector. In case that there is more than 1 closest taxi
     * the index will be of the driver that entered first to the list.
     * @param indexOfTrip the index of the trip at the trips vector that we are search the driver for him.
     * @return the index of the closest taxi or -1 if there is no available driver
     */
    int srcClosestTaxiDriver(int indexOfTrip);

    /**
     * This passenger updating the Driver's current passengers vector be creating a vector of Passenger
     * objects accordingly the number of passengers the we got.
     *
     * @param closestTaxi the driver we should update
     * @param costmSource the source point of the passengers
     * @param costmDest the destination point of the passengers
     * @param numOfPassen the number of passengers we should create
     */
    void updateDriverPassengers(Driver* closestTaxi, Node* costmSource, Node* costmDest,int numOfPassen);

    /**
     * This function sets the trips in the drivers that mach them.
     */
    void connectDriversToTrips(int indexOfTrip);

    /***
     * This function cause the trips to start and make the driver gets to the destination point of the trip
     */
    void startDriving(int i);
    void deleteTripThatEnd(int indexOfTrip);
    Node* getTheNextNode(int indexOfDriver);
};

#endif //APEX2_TAXICENTER_H
