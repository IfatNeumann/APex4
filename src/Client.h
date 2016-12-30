#ifndef APEX4_CLIENT_H
#define APEX4_CLIENT_H

#include "Grid.h"
#include "Driver.h"
class Client {
private:
    Driver* driver;
public:
    /**
     * This function creates a new driver based on the given information.
     * @param id the id of the current driver
     * @param age the age of the current driver
     * @param status the marital of the current driver
     * @param experience the years of experience of the current driver
     * @param texiId the id of the taxi that belong to the current driver
     */
    Driver* createDriver(int id, int age, char status, int experience, int texiId);
};
#endif //APEX4_CLIENT_H
