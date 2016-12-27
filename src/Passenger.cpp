#include "Passenger.h"
Passenger::Passenger(Node* s, Node* d) {
    this->source = s;
    this->destination = d;
    this->satisfaction = 0;

}

Passenger::~Passenger() {
}
void Passenger::setSatisfaction(){
    //random number
}

double Passenger::getSatisfaction(){
    return this->satisfaction;
}

Node* Passenger::getSource(){
    return this->source;
}

Node* Passenger::getDestination(){
    return this->destination;
}
