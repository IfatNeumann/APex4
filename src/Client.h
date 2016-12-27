#ifndef APEX4_CLIENT_H
#define APEX4_CLIENT_H

#include "Grid.h"
#include "Driver.h"
class Client {
private:
    Driver* driver;
public:

        void createDriver(int id, int age, char status, int experience, int texiId);
};
#endif //APEX4_CLIENT_H
