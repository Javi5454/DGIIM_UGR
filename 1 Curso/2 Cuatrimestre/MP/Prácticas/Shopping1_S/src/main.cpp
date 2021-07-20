/**
 * @file main.cpp
 * @author DECSAI
 * @note To be implemented by students 
 * 
 */


#include <string>
#include <cassert>
#include <iostream>
#include "Event.h"

#include "MPTests.h"

using namespace std;


/**
 * @brief displays the content of the array by using the method to_string that easy to transfer data to stream.  The content remains constant
 * @param array of the Events
 * @param nEvent number of events in the array
 */
void print(const Event array[], int &nEvent);

/**
 * @brief Update the counter per week day (value in 0..6) for every event found . 
 * It also shows the computed values on the screen in the following format
 * ~~~~
 *      SUNDAY(0) MONDAY(0) TUESDAY(0) WEDNESDAY(0) THURSDAY(0) FRIDAY(0) SATURDAY(0)
 *      +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+ 
 *      |    |    |    |    |    |
 *      0    5    10   15   20   25
 * ~~~~
 * 
 * @param arrayE an Event input array
 * @param nEvents number of events in arrayE
 * @param arrayA an int output array
 */
void computeActivity(const Event arrayE[], int  nEvents,  int arrayA[]);
/**
 * @brief Compute the  max number of activity events, and the day on which is produced
 * @param arrayA the counter of activities, an input array
 * @param ndays number of days
 * @param maxDay
 * @return maxActivity the counter of events of 
 */
int computeMaxActivityDay(const int arrayA[], int &maxDay, int ndays=7);



/**
 * @brief The main function of the program carries out the following procedure
 *   - It uses a static array of Events to store a sequence of events read from 
 * keyboard (likely to be redirected from a data file in the ./tests folder)
 *   - It reads the maximum number of valid records to be stored in the array.
 *   - If the event read is right (use the method isEmpty() to detect non-valid
 * records), it is stored in the array, otherwise, it is dismissed. Only valid records count.
 *   - Next, it computes the number of events found at each day of the week (complete the implementation
 * of the local function computeActivity() which also shows the result)
 *   - Next, it finds which is the day of highest activity recorded and show it on screen
 */
int main(int argc, char** argv) {
    
    int nEvent;
    int valido = 0;
    
    cin >> nEvent;
    
    Event arrayE[nEvent];
    
    string add;
    
    getline(cin, add);
    
    for (int i = 0; i < nEvent; i++){
     
        getline(cin, add);
        
        Event toAdd(add);
        
        if(toAdd.isEmpty() == false){
            arrayE[valido] = toAdd;
            valido++;
        }
    }
     
    int arrayA[7] = {0};
    
    print(arrayE, valido);
    
    computeActivity(arrayE, valido, arrayA);
    CVAL << endl << "Records read: " << nEvent << endl;
    CVAL << "Valid records: " << valido << endl;
    
    int maxDay = 0;
    int days = 7;
    int maxActivity = computeMaxActivityDay(arrayA, maxDay, days);
    
    CVAL << "Max activity: " << maxActivity << endl;
    CVAL << "Day of Max activity: " << DAYNAME[maxDay] << endl;
    
    return 0;
    
}

void print(const Event array[], int &nEvent) {
    
    for(int i = 0; i < nEvent; i++)
    {
        cout << array[i].to_string();
        cout << endl;
    }

}

void computeActivity(const Event arrayE[], int  nEvents,  int arrayA[]){

    for(int i = 0; i< nEvents; i++)
    {
        DateTime date = arrayE[i].getDateTime();
        int day = date.weekDay();
        
        arrayA[day]++;
    }
    
    CVAL << "Activity found:";
    for (int day=0; day<7; day++) {
        CVAL << " " << DAYNAME[day]<<"("<<arrayA[day]<<")";
    }
    CVAL << endl;
}

int computeMaxActivityDay(const int arrayA[], int &maxDay, int ndays){
    
    int maxActivity = 0;
    
    for(int d = 0; d < ndays; d++)
    {
        if(maxActivity < arrayA[d])
        {
            maxDay = d;
            maxActivity = arrayA[d];
        }
    }
    
    return maxActivity;

}