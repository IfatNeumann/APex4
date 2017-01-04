#ifndef APEX1_NODE_H
#define APEX1_NODE_H
#include "Point.h"
/*
* class Node
* this class is connecting between the grid and the point.
* with this class we can reach a node in the grid by a point value,
* and reach all the node's members.
*/
class Node {
private:
    Point point;
    Node* parent;
    bool visited;
    bool isObstacle;
    Point neighbors[4];
    int numOfNeighbors;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & point;
        ar & parent;
        ar & visited;
        ar & isObstacle;
        ar & neighbors;
        ar & numOfNeighbors;
    }
public:
    Node();
    /*
    * constructor
    * gets two integers and put them in x,y members of the node's point
    */
    Node(int x,int y);
    /*
    * this function returns a pointer to the node's parent
    */
    Node* getParent();
    /*
    * this function sets the node's parent
    */
    void setParent(Node* prnt);
    /*
    * this function returns the point value of the node
    */
    Point getPoint();
    /*
    * this function changes the node's 'visited' member value from 'false' to 'true'
    */
    void setVisited(bool isVisited);
    /*
    * this function returns the node's 'visited' member value
    */
    bool getVisited();
    /*
    * this function changes the node's 'isObstacle' member value from 'false' to 'true'
    */
    void setIsObstacle();
    /*
    * this function returns the node's 'isObstacle' member value
    */
    bool getIsObstacle() { return this->isObstacle; }
    /*
    * this function sets the node's neighbor in the i'th place of the array
    */
    void setNeighbor(Point neighbor,int i);
    /*
    * this function returns the number of neighbors of the node
    */
    int getNumOfNeighbors();
    /*
    * this function increases the number of neighbors of the node
    */
    void increaseNumOfNeighbors();
    /*
    * this function returns the node's neighbor in the i'th place in the array
    */
    Point getNeighbor(int i);
};
#endif //APEX1_NODE_H