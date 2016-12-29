/**
 * Class Passenger.
 * This class is responsible for the passenger's data, Which contains:
 * Source point and destination point. and the satisfaction of the passenger.
 */

#ifndef APEX2_PASSENGER_H
#define APEX2_PASSENGER_H

#include "Point.h"
#include "Node.h"

class Passenger {
private:
    Node* source;
    Node* destination;
    double satisfaction;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & source;
        ar & destination;
        ar & satisfaction;
    }
public:
    Passenger();
    /**
    * Constructor.
    * Gets the passenger's source point and destination point
    * @param s - source point
    * @param d - destination point
    */
    Passenger(Node* s,Node* d);
    /**
     * Destructor.
     */
    ~Passenger();

    /**
     * This function set a random number that will be the satisfaction of this passenger
     * don't relevant for this  exercise
     */
    void setSatisfaction();

    /**
     * This function returns the passenger's satisfation.
     * @return
     */
    double getSatisfaction();

    /**
     * This function returns the passenger's source point.
     * @return source - variable from type pointer to Node
     */
    Node* getSource();

    /**
     * This function returns the passenger's destination point.
     * @return destination - variable from type pointer to Node
     */
     Node* getDestination();
};


#endif //APEX2_PASSENGER_H
