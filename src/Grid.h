#ifndef APEX1_GRID_H
#define APEX1_GRID_H
#include "Node.h"

/*
* class Grid
* this class is our 'world'.
* it has given size and a matrix of pointers to the nodes.
 * this class can reach information about a node's neighbors.
*/
class Grid {
private:
    int height;
    int width;
    Node*** grid;// matrix of Node*
public:
    /*
    * constructor
    * gets two integers and put them in the height and width members
    */
    Grid(int height, int width);
    /*
    * constructor
    */
    Grid();
    /*
    * destructor
    */
    ~Grid();
    /*
    * this function frees the memory that was allocated in the heap for the grid
    */
    void deleteGrid();
    /*
    * this function sets the grid with nodes
    */
    void setGrid();
    /*
    * this function fills the "neighbors" array of each node
    */
    void setNeighbors();
    /*
    * this function receives a point and returns the point's matching node
    */
    Node* getNode(Point p);
    /*
    * this function returns the node's neighbor in the i'th place in the array
    */
    Node* getNeighbor(Node* node,int i);
    /*
    * this function recieves a point and return true if it's in the grid and false otherwise
    */
    bool inTheGrid(Point p);
    void initializeBeforeTrip();
};


#endif //APEX1_GRID_H
