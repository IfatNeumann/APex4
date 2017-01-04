
#ifndef APEX1_POINT_H
#define APEX1_POINT_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
/*
* class Point
* this class is the most basic class.
* this class helps us allocate ourselves in our 'world'.
*/
class Point{
private:
    int x;
    int y;
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & x;
        ar & y;
    }
public:
    /*
    * constructor
    * gets two integers and put them in x,y members
    */
    Point(int newX,int newY);
    /*
    * constructor
    */
    Point();
    /*
    * destructor
    */
    ~Point();
    /*
     * this function returns the x value of the point
     */
    int getX();
    /*
     * this function returns the y value of the point
     */
    int getY();
    /*
     * this function sets the x value of the point
     */
    void setX(int newX);
    /*
     * this function sets the y value of the point
     */
    void setY(int newY);
    /*
     * this function prints the point in a (x,y) format
     */
    void printPoint();
    /*
     * this function returns true if the received point is equal to this point,and false otherwise
     */
    bool isEqualTo(Point p);
};
#endif //APEX1_POINT_H
