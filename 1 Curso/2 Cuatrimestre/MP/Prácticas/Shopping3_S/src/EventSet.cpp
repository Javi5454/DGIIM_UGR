/* 
 * File:   EventSet.cpp
 * @author MP-Team DECSAI
 * @note To be implemented by students 
 */


#include <unordered_map>
#include <fstream>
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
    
    if(field == "DateTime"){
        for(int i = 0; i < es.size(); i++){
            DateTime to_add(value);

            if(to_add.sameDay(es.at(i).getDateTime())){
                result.add(es.at(i));
            }
        }
    }
    else{
        
        for(int i = 0; i < es.size(); i++){
            if(es.at(i).getField(field) == value){
                result.add(es.at(i));
            }
        }
    }
    
    
    
    return result;
    
}

void findUnique(const EventSet& es, const std::string &field, std::string values[], int & n_values) {
    
    n_values = 0;
    
    
    if(field != "DateTime"){
        
    
        for(int i = 0; i < es.size(); i++){

            bool twice = false;

                for(int j = 0; (j < n_values) && (twice == false); j++){

                    if(es.at(i).getField(field) == values[j])
                        twice = true;
                }

                if(twice == false){
                    values[n_values] = es.at(i).getField(field);
                    n_values++;
                }

            }
    }
        
    else{
        
        for(int i = 0; i < es.size(); i++){

            bool twice = false;
        
            for(int j = 0; (j < n_values) && (twice == false); j++){
                
                DateTime date(values[j]);

                if(date.sameDay(es.at(i).getDateTime()))
                    twice = true;
            }

            
            if(twice == false){
                
                string date = es.at(i).getDateTime().to_string();
                
                date.at(11) = '0';
                date.at(12) = '0';
                date.at(14) = '0';
                date.at(15) = '0';
                date.at(17) = '0';
                date.at(18) = '0';
                
                values[n_values] = date;
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

void EventSet::write(ofstream &os) const { 
    string to_add;
    
    for (int i = 0; i < _nEvents; i++){
        to_add += at(i).to_string() + " ";
    }
    
    os << to_add;
}
bool EventSet::read(ifstream &is, int nelements) { 
    Event e;
    bool res = true;
    
    // Limpiar el EventSet
    
    clear();
    
    for(int i=0; (i < nelements)&&res; i++){
        e.read(is);
    
        if(is){
            add(e);
        } else
            res = false;
    }
    
    
    
    return(res);
}

Event NULL_EVENT = Event();