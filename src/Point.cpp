#include <iostream>
#include "Point.h"
#include <stdexcept>
Point::Point(int newX,int newY){
if((newX<0)||(newY<0))
        throw std::invalid_argument("negative axe location");
    x=newX;
    y=newY;
}
Point::Point(){
}
Point::~Point(){
}
void Point::setY(int newY){
if(newY<0)
        throw std::invalid_argument("negative axe location");
    y=newY;
    return;
}
int Point::getX(){
    return x;
}
void Point::setX(int newX){
if(newX<0)
        throw std::invalid_argument("negative axe location");
    x=newX;
    return;
}
int Point::getY(){
    return y;
}
void Point::printPoint(){
    std::cout << "(" <<x<< ","<< y<<")" <<std::endl;
    return;
}
bool Point::isEqualTo(Point p){
    return (x==p.getX()&&y==p.getY());
}
