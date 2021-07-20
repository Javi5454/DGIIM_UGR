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


Index::Index(int onBrand) {
    _nEntries = 0;
    setIOnWhich(onBrand);
    _capacity = 0;
    _entries = nullptr;
}

void Index::deallocate(){
    if(_entries != nullptr){
        delete [] _entries;
        _entries = nullptr;
        _capacity = 0;
        _nEntries = 0;
    }
    
}


void Index::copy(const Index & orig){
    deallocate();
    
    _entries = new Pair [orig._capacity];
    _capacity = orig._capacity;
    
    for (int i = 0; i < orig.size(); i++){
        _entries[i] = orig.at(i);
    }
    
    _nEntries = orig.size();
}

void Index::copy (Pair *dest){
    dest = _entries;
}

Index::Index(const Index & orig){
    _entries = nullptr;
    _capacity = 0;
    _onBrand = 0;
    copy(orig);
}


void Index::reallocate(int size){
    int target = _capacity + size;
    
    while (_capacity < target){
        _capacity = 2*_capacity + 1;
    }
    
    Pair *aux = new Pair [_capacity];
    
    for (int i = 0; i < _nEntries; i++){
        aux[i] = _entries[i];
    }
    
    delete [] _entries;
    
    _entries = aux;
    aux = nullptr;
    
}



void Index::setIOnWhich(int val) {
    if((val == 1) || (val == 0) || (val == 2)){
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
    deallocate();
}

int Index::getIOnWhich() const {
    return _onBrand;
}

int Index::add(const Pair & pair) {
    int pos = upper_bound(pair.getKey());
    
    if(_nEntries >= _capacity){
        reallocate(1);
    }
    
    if(pair.isEmpty() == false){
        
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
    else if (getIOnWhich() == 2){
        for (int i = 0; i < evSet.size(); i++){
            string session_check = evSet.at(i).getSession();
            
            if(session_check != ""){
                Pair to_add(session_check, i);
                add(to_add);
            }
        }
    }
}

int Index::lower_bound(const string & key) const {
    int l = 0, r = _nEntries -1;
    while (l <= r) {
        int mid = (r-l)/2+l;
        if (_entries[mid].getKey() < key){
            l = mid+1;
        }
        else{
            r = mid-1;
        }
    }
    return l;
}


int Index::upper_bound(const string & key) const {
    int left = 0;
    int result = 0;
    int right = _nEntries - 1;
    int center = 0;
    bool keep = true;
    
    while (left <= right && keep){
        center = (left+right)/2;
        
        if(_entries[center].getKey() < key){
            left = center + 1;
            result = center;
        }
        else if (_entries[center].getKey() > key){
            right = center - 1;
            result = center;
        }
        else{
            result = center;
            keep = false;
        }
    }
    
    keep = true;
    
    for (int i = result; i < _nEntries & keep; i++){
        if(_entries[i].getKey() <= key){
            result = i+1;
        }
        else{
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

Index::~Index(){
    deallocate();
}

Index & Index::operator=(const Index &one){
    if(this!=&one){
        copy(one);
    }
    
    return *this;
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