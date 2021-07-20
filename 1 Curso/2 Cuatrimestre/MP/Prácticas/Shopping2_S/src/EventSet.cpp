/* 
 * File:   EventSet.cpp
 * @author MP-Team DECSAI
 * @note To be implemented by students 
 */


#include <unordered_map>
#include "EventSet.h"

using namespace std;


/**
 * @brief Give string[] and a string, it searches for string within string[]
 * @param array     The set of strings to look for
 * @param n_array   The size of string[]
 * @param name      The string that is being seeked
 * @return          The position of the first occurrence of string within string[]
 *  -1 if the string does not belong to string[]
 */
int findString(const string array[], int n_array, const string & name) {
    int result = -1;
    
    for(int i = 0; i < n_array; i++){
        if(array[i] == name){
            result = i;
        }
    }
    
    return result;

}

std::string EventSet::to_string() const {
    string result;
    result = std::to_string(_nEvents) + " ";
    for (int i = 0; i < _nEvents; i++)
        result += _events[i].to_string() + "\n";
    return result;
}

EventSet::EventSet() {
    _nEvents = 0;
}

int EventSet::size() const {
    return _nEvents;
}


void EventSet::clear() {
    _nEvents = 0;
}

int EventSet::add(const Event & e) {
    
    if(_nEvents < MAXEVENT)
    {
        _events[_nEvents] = e;
        _nEvents++;
        return 1;
    }
    else
    {
        return 0;
    }

}

int EventSet::add(const std::string& line) {
    
    if(_nEvents < MAXEVENT)
    {
        Event to_add(line);
        _events[_nEvents] = to_add;
        _nEvents++;
        return 1;
    }
    else
    {
        return 0;
    }
    

}

const Event & EventSet::at(int pos) const {
    
    if((0 <= pos) && (pos < _nEvents))
    {
        return _events[pos];
    }
    else
    {
        return NULL_EVENT;
    }
}


EventSet rawFilterEvents(const EventSet& es, const std::string &field, const std::string &value) {
    
    EventSet result;
    
    for(int i = 0; i < es.size(); i++){
        if(es.at(i).getField(field) == value){
            result.add(es.at(i));
        }
    }
    
    return result;
    
}

void findUnique(const EventSet& es, const std::string &field, std::string values[], int & n_values) {
    
    n_values = 0;
    
    if(es.size() > 0){
        values[0] = es.at(0).getField(field);
        n_values++;
        bool add = true;

        for(int i = 1; i < es.size(); i++){

            for(int k = 0; k < i; k++){
                if(values[k] != es.at(i).getField(field)){
                    add = true;
                }
                else
                {
                    add = false;
                    k = i+1;
                }
            }

            if (add){
                values[n_values] = es.at(i).getField(field);
                n_values++;
            }
        }
        
    }
}

float sumPrice(const EventSet & evSet) {
    float result = 0;
    
    for(int i = 0; i < evSet.size(); i++){
        result += evSet.at(i).getPrice();
    }
    
    return result;
}

Event NULL_EVENT = Event();