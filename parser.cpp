
// handles the json files of the MBTA API and pulls relevant data.
//Bus Stop: https://api-v3.mbta.com/stops/1315
//Green Line: https://api-v3.mbta.com/stops/70254

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
//Define what a transport is
struct Transport
{
    Vehichle type; //Type of vehicle
    char * id; //c-string id.
    unsigned int arrival; //Time of arrival (should never be negative)
    //How full things are looking
};

//To Do:
// FIFO List that holds all the currently new Transports.
// Build Parser to pull to create new Transports at a set interval.
// Print the data out.
// Some kind of scheduler that knocks off items that arrival is past current time.

