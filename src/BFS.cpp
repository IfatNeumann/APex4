#include <iostream>
#include "BFS.h"

BFS::BFS(Grid* g){
    grid = g;
}

BFS::~BFS(){
}

std::stack<Point> BFS::bfs(Node* startN, Node* destN){//destination
    Node* neighbor;
    //in case the starting point and the destination point are equal (edge case)
    if((*startN).getPoint().isEqualTo((*destN).getPoint())){
        way.push((*startN).getPoint());
        return way;
    }
    nodes.push(startN);
    (*startN).setVisited();
    while (!nodes.empty()){
        Node *thisNode = nodes.front();
        for (int i=0;i<thisNode->getNumOfNeighbors();i++) { //for each neighbor
            neighbor = grid->getNeighbor(thisNode, i);
            if (!neighbor->getVisited()) {//if not visited
                neighbor->setVisited();
                neighbor->setParent(thisNode);
                nodes.push(neighbor);
                if (neighbor->getPoint().isEqualTo((*destN).getPoint())) {
                    // got to destination!
                    way.push(neighbor->getPoint());
                    do{//until we get to the starting node
                        way.push(thisNode->getPoint()); //start filling the stack
                        thisNode = (thisNode->getParent());
                    }while ((thisNode!=NULL)&&!thisNode->
                            getPoint().isEqualTo((*startN).getPoint()));
                    if(thisNode!=NULL)
                        way.push(thisNode->getPoint());
                    return way;
                }
            }
        }
        nodes.pop();
    }
    return way;
}