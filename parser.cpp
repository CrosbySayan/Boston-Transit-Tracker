#include <iostream>
#include <string>
#include "transport_def.cpp"
using namespace std;
// handles the json files of the MBTA API and pulls relevant data.
//Bus Stop: https://api-v3.mbta.com/stops/1315
//Green Line: https://api-v3.mbta.com/stops/70254

// Predictions: https://api-v3.mbta.com/predictions?filter[stop]=1315
//     /Here
//    /
// - [] - [=-=-=] - []
//

//Max Length Linked List FIFO
struct node {
   p_Ride elem;
   node * next;
};

struct queue {
    int MAX_LENGTH;
    node * head;
    node * tail;
};

bool empty(struct queue * queue) {
    return (queue->head == NULL);
}

void push(struct queue * queue, p_Ride elem) {
    node * new_elem = new node{elem, NULL};
    if(empty(queue)) {
        queue->head = new_elem;
        queue->tail = new_elem;
    } else {
        queue->tail->next = new_elem;
        queue->tail = new_elem;
    }
}

p_Ride pop(struct queue * queue) {
    if(empty(queue)) {
        return NULL;
    }

    
}

//To Do:
// FIFO List that holds all the currently new Transports.
// Build Parser to pull to create new Transports at a set interval.
// Print the data out.
// Some kind of scheduler that knocks off items that arrival is past current time.

int main() {
    Ride r = {BUS, NO_DATA_AVAILABLE, INCOMING_AT, "y1234", 1205};

    cout << r.arrival << endl;
    return 0;
}