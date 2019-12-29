//
//  main.cpp
//  Analysis of Algorithms - Homework 2
//
//  Created by Medina Zaganjori on 12.12.2019.
//  Copyright © 2019 Medina Zaganjori. All rights reserved.
//
#include <iostream>
#include<algorithm>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include <string.h>
#include <iostream>
#include <cstring>
#include <cstdlib>

#define TOTAL_LINE 10
using namespace std;

class Event{
public:
    string limit; //either start or end
    string type_event; //A,B,C..
    int event_time;
    Event(string, int, string);
    string getEventType();
    string getLimit();
    int getEventTime();
   // Event(Event &);
};

void Swap(vector <Event> &, int,int);
void buildHeap(vector <Event> &);
void heapify(vector <Event>, int, int);
void heapSort(vector <Event> , int n);
int FindMax(vector <Event>);
int numLines();

string Event::getEventType() {
    return type_event;
}

string Event::getLimit() {
    return limit;
}

int Event::getEventTime() {
    return event_time;
}
Event::Event(string type_event, int event_time, string limit) {
    this->type_event = type_event;
    this->event_time = event_time;
    this->limit = limit;
}
int main(int argc, char *argv[]) {
    //Getting file names and arguments
    ifstream inEvent(argv[1]);

    //Opening the file
    //vector to hold objects
    vector<Event> all_events;

    if (!inEvent.is_open()) {
        cout << "File cannot open" << endl;
        return 0;
    }
    else {
        int j = 0;
        string limit, type_event;
        string event_time;
        string limit1,type_event1,event_time1;
        string line;

        int total = numLines();
        //cout <<total<<endl;
        //extract first 2 columns and then first and third column
        if(inEvent.good()) {
            for (int i = 0; i < total; i++) {
                getline(inEvent, type_event, ' ');
                getline(inEvent, event_time, ' ');
                getline(inEvent, event_time1, '\n');
                all_events.push_back(Event(type_event, (atoi(event_time.c_str())), "STARTED"));
                all_events.push_back(Event(type_event, (atoi(event_time1.c_str())), "ENDED"));
                //}
                //cout << "Reading from file is completed" << endl;
            }
        }
        inEvent.close();

        //print all events at a time

        buildHeap(all_events);
        /*
        //cout<< "my size is "<<all_events.size()<<endl;
       //heapSort(all_events, all_events.size());
        for(int medina = 0;medina<all_events.size();medina++){
            cout<< all_events[medina].getEventType()<<" ";
            cout<< all_events[medina].getEventTime()<<" ";
            cout<< all_events[medina].getLimit()<<" "<<endl;
        }*/
        int max = FindMax(all_events); //program will get repeated until the maximum time will be reached for an event
       //cout<<max<<endl;
        //fix the timer
        int timer =1;
        for (; timer < max;) {
            if (timer != all_events[0].getEventTime()) {
                cout << "TIME " << timer << ": NO EVENT" << endl;
                //timer++;
            }
            while (timer == all_events[0].getEventTime()) {
                cout << "TIME " << timer << ": " << all_events[0].getEventType() << " " << all_events[0].getLimit()
                     << endl;
                all_events.erase(all_events.begin());
                 if (all_events.empty()) {
                    //timer++;
                     cout << "TIME " << timer << ": No available events to execute" << endl;
                     break;
                 }
                 buildHeap(all_events);
             }
               timer++;
            }
        if(timer >=max){
            cout <<"TIME "<< timer-1<<": NO MORE EVENTS, SCHEDULER EXITS"<<endl;
        }

        }

    return 0;
}
void heapify(vector<Event> all_events, int n, int i){
    int smallest = i; // Initialize largest as root
    int l = 2*i + 1; // left = 2*i + 1
    int r = 2*i + 2; // right = 2*i + 2

    // If left child is smaller than root
    if (l <= n && all_events[l].getEventTime() < all_events[i].getEventTime())
        smallest = l;
    // If right child is smaller than smallest so far
    if (r <= n && all_events[r].getEventTime() < all_events[smallest].getEventTime())
        smallest = r;
    // If smallest is not root
    if (smallest != i)
    {
        swap(all_events[i], all_events[smallest]);
        // Recursively heapify the affected sub-tree
        heapify(all_events, n, smallest);
    }
}
void heapSort(vector<Event> all_events, int n){
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(all_events, n, i);
    // One by one extract an element from heap
    for (int i=n-1; i>=0; i--)
    {
        // Move current root to end
        swap(all_events[0], all_events[i]);
        // call min heapify on the reduced heap
        heapify(all_events, i, 0);
    }
}
void buildHeap(vector <Event> &all_events){
    for(int i = (all_events.size()-1) / 2; i>=0;i--){
        heapify(all_events,all_events.size()-1,i);
    }
}
int FindMax(vector<Event> all_events){
    // Initialize minimum element
    int max = all_events[0].getEventTime();
    // Traverse vector elements
    for (int i = 1; i < all_events.size(); i++)
        if (all_events[i].getEventTime() > max)
            max = all_events[i].getEventTime();
    return max;
}
int numLines(){
    int count = 0;
    string line;
    /* Creating input filestream */
    ifstream file("events.txt");
    while (getline(file, line))
    count++;
    //cout << "Numbers of lines in the file : " << count << endl;
    return count;
}