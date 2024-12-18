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

enum Occupancy {
    EMPTY,
    MANY_SEATS_AVAILABLE,
    FEW_SEATS_AVAILABLE,
    STANDING_ROOM_ONLY,
    CRUSHED_STANDING_ROOM_ONLY,
    FULL,
    NOT_ACCEPTING_PASSENGERS,
    NO_DATA_AVAILABLE
};

enum Status {
    INCOMING_AT, //About to arrive at thee stop
    STOPPED_AT, //The Vehichle is standing at the stop.
    IN_TRANSIT_TO //The Vehichle is in between stops (in stop_sequence it will say n+1 what it was from)
};

//A Ride is defined as public transportation module that will
//get a client from their TO stop to their FROM stop.
//Holds information about the id in the
struct Ride
{
    Vehichle type;          //Type of vehicle
    Occupancy occup_status; //The fullness of the vehichle TBI
    Status train_status;    //The status of the train between stops.
    string id;              //The vehichles tag
    int arrival;            //Time of arrival
};
typedef Ride * p_Ride;

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