/* 
 * File:   Index.cpp
 * @author MP-Team DECSAI
 * @warning To be implemented by students 
 */
#include <string>
#include <iostream>
#include <fstream>
#include "Index.h"

using namespace std;

Index::Index()  {
    _nEntries = 0;
    _onBrand = 0;
}

Index::Index(int onBrand) {
    _nEntries = 0;
    setIOnWhich(onBrand);
}

void Index::setIOnWhich(int val) {
    if((val == 1) || (val == 0)){
        _onBrand = val;

    }
    else{
        _onBrand = 0;
    }
}

int Index::size() const {
    return _nEntries;
}

void Index::clear() {
    _nEntries = 0;
}

int Index::getIOnWhich() const {
    return _onBrand;
}

int Index::add(const Pair & pair) {
    int pos = upper_bound(pair.getKey());
    
    if((_nEntries < MAXEVENT) && (pair.isEmpty() == false)){
        
        for (int i = _nEntries; (i > pos); i--){
            _entries[i] = _entries[i-1];
        }
        _entries[pos] = pair;
        _nEntries++;
       
        return 1;
    }
    else{
        return 0;
    }
}


void Index::build(const EventSet & evSet, int onBrand) {
    clear();
    setIOnWhich(onBrand);
    
    if(getIOnWhich() == 0){
        for(int i = 0; i < evSet.size(); i++){
            string user_check = evSet.at(i).getUserID();
                
            if(user_check != ""){
                Pair to_add(user_check, i);
                add(to_add);
            }
        }

    }
    else if (getIOnWhich() == 1){
        for(int i = 0; i < evSet.size(); i++){
            string brand_check = evSet.at(i).getBrand();
            
            if(brand_check != ""){
                Pair to_add(brand_check, i);
                add(to_add);
            }
        }
        
    }
}

int Index::lower_bound(const string & key) const {
    int result = 0;
    bool keep = true;
    
    for(int i = 0; (i < _nEntries) && (keep); i++){
        if (_entries[i].getKey() >= key){
            result = i;
            keep = false;
        }
    }
    
    return result;
}


int Index::upper_bound(const string & key) const {
    int result = _nEntries;
    bool keep = true;
    
    for (int i = 0; (i < _nEntries) && (keep); i++){
        if (key < _entries[i].getKey()){
            result = i;
            keep = false;
        }
    }
    return result;
}

const Pair & Index::at(int pos) const {
    return _entries[pos];
}

Pair & Index::at(int pos) {
   return _entries[pos];
}

void Index::print()const {
    cout << _nEntries << "pairs" << endl;
}

Event getEvent(const EventSet & evSet, const Index & indx, int pos) {
    
    int pos_set = indx.at(pos).getPos();
    
    return evSet.at(pos_set);
    
}

void write(ofstream &os, const EventSet & evSet, const Index & indx) {
    for(int i = 0; i < indx.size(); i++){
        os << getEvent(evSet, indx, i).to_string();
    }
}

Index rawFilterIndex(const EventSet & evSet, const Index & indx, const std::string &field, const std::string &value) {
    Index result(indx.getIOnWhich());
    
    for (int i = 0; i < indx.size(); i++){
        string to_check = evSet.at(indx.at(i).getPos()).getField(field);
        
        if(to_check == value){
            result.add(indx.at(i));
        }
    }
    
    return result;
}

float sumPrice(const EventSet & evSet, const Index & indx) {
    float result = 0;
    
    for (int i = 0; i < indx.size(); i++){
        result += getEvent(evSet, indx, i).getPrice();
    }
    
    return result;
}