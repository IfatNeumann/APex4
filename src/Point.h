#ifndef APEX1_POINT_H
#define APEX1_POINT_H
/*
* class Point
* this class is the most basic class.
* this class helps us allocate ourselves in our 'world'.
*/
class Point{
private:
    int x;
    int y;
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
