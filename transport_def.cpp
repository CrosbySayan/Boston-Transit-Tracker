#include <string>
using namespace std;
//Builds out a lot of definitions to be used by other executables.

//Type of Vehichle as outlined in MBTA's API
enum Vehichle {
    LIGHT_RAIL,
    HEAVY_RAIL,
    COMMUTER_RAIL,
    BUS,
    FERRY
};

//Defines the options of seats (not fully implemented in many transports in Boston)
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

//Defines the state a Vehichle is in on its trip,
// - Either at a stop.
// - About to arrive at a stop.
// - Moving to a stop.
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

//Defines a stop with it's id and the sequence in the route.
struct Stop {
    string id;
    string desc;
    int stop_sequence;
};