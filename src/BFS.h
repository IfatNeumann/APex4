#ifndef APEX1_BFS_H
#define APEX1_BFS_H
#include "Grid.h"
#include <stack>
#include <queue>
#include <iostream>
/*
* class BFS
* this class is responsible to find and print the shortest way
* to the destination node from the starting node.
*/
class BFS {
private:
    Grid* grid;
    std::stack<Point> way;
    std::queue<Node*> nodes;
public:
    /*
    * constructor
    * gets a grid and puts it in his 'grid' member
    */
    BFS(Grid *g);
    /*
    * destructor
    */
    ~BFS();
    /*
    * this function receives a starting and a destination point, and finds the shortest way between them
    */
    std::stack<Point> bfs(Node* start, Node* dest);
};
#endif //APEX1_BFS_H
