/**
 * Class MainFlow.
 * This class is responsible for the flow of the program.
 * It has three members: A taxi center, A grid, A vector 'cabsVector' that contains all the
 * cabs in the program.
 */

#ifndef APEX2_MAINFLOW_H
#define APEX2_MAINFLOW_H

#include <cstdlib>
#include <vector>
#include "TaxiCenter.h"
#include "MaritalStatus.h"
#include "Grid.h"
#include "StandardCab.h"
#include "LuxuryCab.h"

class MainFlow {
private:
    TaxiCenter* myTaxiCenter;
    Grid* grid;
    vector<Cab*> cabsVector;

public:
    /**
     * Constructor.
     */
    MainFlow();

    /**
     * Destructor.
     */
    ~MainFlow();

    /**
     * This function returns a pointer to the taxi center.
     * @return myTaxiCenter
     */
    TaxiCenter* getTaxiCenter();

    /**
     * This function returns the vector of the cabs.
     * @return cabsVector
     */
    vector<Cab*> getCabsVector();

    /**
     * This function creates a new driver based on the given information.
     * @param id the id of the current driver
     * @param age the age of the current driver
     * @param status the marital of the current driver
     * @param experience the years of experience of the current driver
     * @param texiId the id of the taxi that belong to the current driver
     */
    void createDriver(int id,int age,char status,int experience,int texiId);

    /**
     * This function creates a new cab based on the given information.
     * @param idTaxi the id of the current cab
     * @param typeOfTaxi the type of the current cab
     * @param manufacturer the manufacturer of the current cab
     * @param color the color of the current cab
     */
    void createCab(int idTaxi,int typeOfTaxi,char manufacturer,char color);

    /**
     * This function creates a new trip information based on the given information.
     * @param tripId the id of the current trip
     * @param xStartPoint the x value of start point of the current trip
     * @param yStartPoint the y value of start point of the current trip
     * @param xEndPoint the x value of end point of the current trip
     * @param yEndPoint the y value of end point of the current trip
     * @param numOfpassn the number of the passengers of the current trip
     * @param tariff the tariff of the current trip
     */
    void createTripInfo(int tripId, int xStartPoint,int yStartPoint, int xEndPoint, int yEndPoint,int numOfpassn,
    double tariff);

    /**
     * This function creates a grid based on the given information.
     * @param gridY one of the grade that composed the grid
     * @param gridX one of the grade that composed the grid
     */
    void createGrid(int gridX,int gridY);

    /**
     * This function returns a pointer to the grid.
     * @return grid
     */
    Grid* getGrid();

    void mainFlow();
};
#endif //APEX2_MAINFLOW_H
