#include <iostream>
#include <string>
using namespace std;
// handles the json files of the MBTA API and pulls relevant data.
//Bus Stop: https://api-v3.mbta.com/stops/1315
//Green Line: https://api-v3.mbta.com/stops/70254

// Predictions: https://api-v3.mbta.com/predictions?filter[stop]=1315
//     /Here
//    /
// - [] - [=-=-=] - []
//
enum Vehichle {
    LIGHT_RAIL,
    HEAVY_RAIL,
    COMMUTER_RAIL,
    BUS,
    FERRY
};

enum Status {
    INCOMING_AT, //About to arrive at thee stop
    STOPPED_AT, //The Vehichle is standing at the stop.
    IN_TRANSIT_TO //The Vehichle is in between stops (in stop_sequence it will say n+1 what it was from)
}

//A Ride is defined as public transportation module that will
//get a client from their TO stop to their FROM stop.
//Holds information about the id in the
struct Ride
{
    Vehichle type; //Type of vehicle
    int id; //all id's are numbers with the starting prefix y.

    unsigned int arrival; //Time of arrival (should never be negative)
};

struct Stop {
    int id;
    int stop_sequence;
}

//To Do:
// FIFO List that holds all the currently new Transports.
// Build Parser to pull to create new Transports at a set interval.
// Print the data out.
// Some kind of scheduler that knocks off items that arrival is past current time.

int main() {
    cout << "Hello World" << endl;
    return 0;
}