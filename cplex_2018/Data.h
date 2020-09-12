#pragma once
#include <list>
#include <vector>

#include "Flight.h"
#include "Deport.h"
#include "Passenger.h"

using namespace std;

class Data {
public:
    int flightNum;
    int parkNum;
    int passengerNum;


    vector<Flight> flightList;
    vector<Deport> deportList;
    vector<Passenger> passengerList;

    vector<vector<int>> isTypeMatching;
    vector<vector<int>> isConflict;

    vector<vector<int>> tranTime = { {15, 20, 20, 15},
                                     {35, 40, 40, 35},
                                     {35, 40, 40, 45},
                                     {20, 30, 30, 20}
                                   };
};