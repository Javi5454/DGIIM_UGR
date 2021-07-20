/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newmain.cpp
 * Author: javi5454
 *
 * Created on May 10, 2021, 6:39 PM
 */

#include <cstdlib>
#include <iostream>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    int example[8] = {10, 20, 30, 30, 40, 50, 60, 70};
    int key = 40;
    int result;
    
    int right = 8 - 1;
    int left = 0;
    int center;
    bool keep = true;
    
    while (left <= right && keep){
        center = (left+right)/2;
        
        if(example[center] < key){
            left = center + 1;
            result = center;
        }
        else if (example[center] > key){
            right = center - 1;
            result = center;
        }
        else{
            result = center;
            keep = false;
        }
    }
    
    keep = true;
    
    for (int i = result; i < 8 & keep; i++){
        if(example[i] > key){
            keep = false;
            result = i;
        }
    }
    
    cout << result;

    return 0;
}

