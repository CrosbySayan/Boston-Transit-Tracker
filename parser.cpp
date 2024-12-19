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
    unsigned int MAX_LENGTH;
    unsigned int current_length = 0;
    node * head;
    node * tail;
};

bool empty(struct queue * queue) {
    return (queue->head == NULL);
}

void push(struct queue * queue, p_Ride elem) {
    node * new_elem = new node{elem, NULL};
    queue->current_length++;
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
    node * tmp = queue->head;
    queue->head = queue->head->next;
    tmp->next = NULL;
    p_Ride elem = tmp->elem;
    delete tmp;
    return elem;
}

queue current = {4, 0, NULL, NULL};
//To Do:
// FIFO List that holds all the currently new Transports.
// Build Parser to pull to create new Transports at a set interval.
// Print the data out.
// Some kind of scheduler that knocks off items that arrival is past current time.

int main() {
    Ride r = {BUS, NO_DATA_AVAILABLE, INCOMING_AT, "y1234", 1205};
    Ride b = {LIGHT_RAIL, NO_DATA_AVAILABLE, STOPPED_AT, "G-1302", 1206};
    push(&current, &r);
    push(&current, &b);
    pop(&current);
    cout << current.head->elem->id << endl;
    cout << current.tail->elem->id << endl;
    return 0;
}