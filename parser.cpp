#include <iostream>
#include <string>
#include "transport_def.cpp"
//Networking
#include <curl/curl.h>

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
// Build Parser to pull to create new Transports at a set interval.
// Some kind of scheduler that knocks off items that arrival is past current time.

//--------------------------------------------|
// P A R S I N G  D A T A                     |
//--------------------------------------------|
size_t write_data(void* buffer, size_t size, size_t nmemb, void* userp);

void run_parser() {
    CURL *handle = curl_easy_init();
    cout << "Running" << endl;
    curl_easy_setopt(handle, CURLOPT_URL, "https://api-v3.mbta.com");

    CURLcode res = curl_easy_perform(handle);
    if(res != CURLE_OK) {
        cerr << "Request Failed: " << curl_easy_strerror(res)<<endl;
    }
    curl_easy_cleanup(handle);
}

//-------------------------------------------/
// P R E T T Y   P R I N T                  /
//_________________________________________/

void prettyPrint(struct queue * queue) {
    node * ptr = queue->head;
    while(ptr != NULL) {
        p_Ride ride = ptr->elem;
        cout << "ID: " + ride->id + " | ";
        cout << ride->arrival;
        ptr = ptr->next;
        cout << "\n";
    }
}

int main() {
    Ride r = {BUS, NO_DATA_AVAILABLE, INCOMING_AT, "y1234", 1205};
    Ride b = {LIGHT_RAIL, NO_DATA_AVAILABLE, STOPPED_AT, "G-1302", 1206};
    push(&current, &r);
    push(&current, &b);
    prettyPrint(&current);
    run_parser();
    return 0;
}