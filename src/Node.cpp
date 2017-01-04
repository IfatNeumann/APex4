#include "Node.h"
#include <iostream> //for the NULL
#include <stdexcept>
Node::Node(){

}
Node::Node(int x,int y){
    point.setX(x);
    point.setY(y);
    parent= NULL;
    visited = false;
    isObstacle = false;
    numOfNeighbors = 0;
}
bool Node::getVisited() {
    return visited;
}
void Node::setIsObstacle() {
    isObstacle = true;
    return;
}
/*bool Node::getIsObstacle() {
    return isObstacle;
}*/
 Node* Node::getParent(){
  return parent;
 }
void Node::setParent(Node* prnt){
    parent = prnt;
}
Point Node::getPoint(){
    return point;
}
void Node::setVisited(bool isVisited){
    visited = isVisited;
}
void Node::setNeighbor(Point neighbor,int i){
if(i>3||i<0)
        throw std::invalid_argument("wrong index");    
neighbors[i] = neighbor;
    return;
}
Point Node::getNeighbor(int i){
if(i>4||i<0)
        throw std::invalid_argument("wrong index");
    return neighbors[i];
}
void Node::increaseNumOfNeighbors(){
    numOfNeighbors++;
}

int Node::getNumOfNeighbors() {
    return numOfNeighbors;
}
