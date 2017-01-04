#include "Grid.h"
#include <stdexcept>
#include <iostream>

Grid::Grid(int w, int h) {
    height = h;
    width = w;
    grid = new Node**[width];
    for (int i=0;i<width;i++)
        grid[i] = new Node*[height];
    setGrid();
}

Grid::Grid() {
}

Grid::~Grid(){
    deleteGrid();
}

void Grid::deleteGrid(){
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; j++) {
            delete grid[i][j];
        }
        delete[] grid[i];
    }
    delete[] grid;
}

void Grid::setGrid() {
    for (int i=0;i<width;i++){
        for (int j=0;j<height;j++){
            grid[i][j] = new Node(i,j);
        }
    }
    setNeighbors();
}

void Grid::setNeighbors() {
    for (int i=0;i<width;i++){
        for (int j=0;j<height;j++){
            if ((0<=i-1)&&(!((grid[i-1][j])->getIsObstacle()))) {//9 o'clock
                grid[i][j]->setNeighbor(Point(i-1,j),grid[i][j]->getNumOfNeighbors());
                grid[i][j]->increaseNumOfNeighbors();
            }
            if ((j+1<height)&&(!((grid[i][j+1])->getIsObstacle()))) {//12 o'clock
                grid[i][j]->setNeighbor(Point(i,j+1),grid[i][j]->getNumOfNeighbors());
                grid[i][j]->increaseNumOfNeighbors();
            }
            if ((i+1<width)&&(!((grid[i+1][j])->getIsObstacle()))) {//3 o'clock
                grid[i][j]->setNeighbor(Point(i+1,j),grid[i][j]->getNumOfNeighbors());
                grid[i][j]->increaseNumOfNeighbors();
            }
            if ((0<=j-1)&&(!((grid[i][j-1])->getIsObstacle()))) {//6 o'clock
                grid[i][j]->setNeighbor(Point(i,j-1),grid[i][j]->getNumOfNeighbors());
                grid[i][j]->increaseNumOfNeighbors();
            }
        }
    }
}

Node* Grid::getNeighbor(Node* node,int i){
    return getNode(node->getNeighbor(i));
}

bool Grid::inTheGrid(Point p){
    return ((p.getY()<height)&&(p.getX()<width));
}
Node* Grid::getNode(Point p){
    if(!inTheGrid(p))
        throw std::invalid_argument("point not in the grid");
    return grid[p.getX()][p.getY()];
}

void Grid::initializeBeforeTrip(){
    for (int i=0;i<width;i++){
        for (int j=0;j<height;j++){
            grid[i][j]->setVisited(false);
            grid[i][j]->setParent(NULL);
        }
    }
}