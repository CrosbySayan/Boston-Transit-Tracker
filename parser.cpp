#include <iostream>
#include <string>
#include "transport_def.cpp"
//Networking
#include <curl/curl.h>
//Parseing
#include "jsoncpp/jsoncpp.cpp"
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

//This function needs to write the data into a usable string buffer to buffered for our purposes
size_t write_data(char * buffer, size_t size, size_t nmemb, string * userp) {
    const size_t total_bytes(size * nmemb);
    userp->append(buffer, total_bytes);
    return total_bytes;
}

//Runs a simple curl pull and puts it into a string
void run_curl_pull() {
    CURL *handle = curl_easy_init();
    cout << "Running" << endl;
    curl_easy_setopt(handle, CURLOPT_URL, "https://api-v3.mbta.com/stops/70254");
    //More setopt operations to configure how we want to curl
    string * httpData(new string);
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, httpData);
    CURLcode res = curl_easy_perform(handle);
    if(res != CURLE_OK) {
        cerr << "Request Failed: " << curl_easy_strerror(res)<<endl;
    }
    //cout << *httpData << endl;
    curl_easy_cleanup(handle);

    Json::Value jsonData;
    Json::Reader jsonReader;
    if (jsonReader.parse(*httpData, jsonData)) {
         cout << jsonData.toStyledString() << endl;
    }
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
    run_curl_pull();
    return 0;
}