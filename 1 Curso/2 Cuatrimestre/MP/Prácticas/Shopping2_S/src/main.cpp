/* 
 * File:   main.cpp
 * @author MP-Team DECSAI
 * @warning To be implemented by students 
 */

#include <string>
#include <cassert>
#include <iostream>
#include <cstring>
#include "MPTests.h"
#include "Event.h"
#include "EventSet.h"
#include "DataVector.h"
#include "DataTable.h"


using namespace std;

/**
 * @brief Update the counter per week day (value in 0..6) for every event found . 
 * It also shows the computed values on the screen
 * @param evSet an input EventSet  
 * @param arrayA an int output array
 */

void computeActivity(const EventSet & evSet, int arrayA[]);
/**
 * @brief This program must load a sample dataset given by keyboard, but really
 * redirected from a disk data file. Introduce in an EventSet only those records non
 * empty, and then produce the following reports
 *   - Inform about the total number of records read
 *   - Filter this EvenSet and extract only those of type "purchase". Let us call it
 *     "purchaseSet". Inform of its size.
 *   - Take purchaseSet and produce the following reports
 *       - How many sales have been detected each day of the week. Something like
 *~~~~ 
 *    Sales/Weekday 3 records
 *         0         1        2  
 *    SUNDAY    MONDAY  TUESDAY
 *~~~~
 *       - Extract the unique set of brands in purchaseSet and find the amount of money
 * sold by every brand. Please take into account that this field might be empty, that is
 * "", therefore, it will appear as an "unknown" brand marked with the empty string "". 
 * Something like
 * ~~~~
 *      $$/Brand    103.25 US$
 *      brand1     100.10
 *      brand2       3.15
 *      ...
 * ~~~~
 *       - Extract the unique set of Users in purchaseSet and find how how many products
 * have bought every User. Something like.
 * ~~~~
 *      QTY/User    3 records
 *      user1       1
 *      user2       1
 *      user3       1
 * ~~~~
 *   - At every report you are suggested to use the class DataVector. Let say we have the following data
 * ~~~~
 *      string brands [2]={"brand1", "brand2"}
 *      int nbrands = 2;
 *      double salesByBrand [2]={100.10,3.15}
 *      int nsales = nbrands;
 * ~~~~
 *   - The report might be made by hand or making use of the class DataVector and its methods
 * boths showReport() which shows a report on the screen, and reportData() which encodes its content as
 * an encrypted long number which may be easily transferred or compared. In order to do that,
 * the following steps could be carried out
 * 
 * ~~~
 *    DataVector brandData;
 * 
 *    brandData.alloc(nbrands);
 *    brandData.setTitle(""$$/Brand");
 *    brandData.loadLabels(brands);
 *    brandData.loadValues(salesByBrand);
 *    cout << brandData.showPlainReport(2); // Number od decimal digits
 *    REPORT_DATA(brandData);
 * ~~~
 * 
 *   
 * @return 
 */
int main() {

    Event one;
    EventSet eventS, aux;
    int n2Read = 0, nEvents = 0;
    string add;

    // 1. Read the events from the dataset and load them in a EventSet 
    //    only the correct ones will be charged on the EventSet
    
    cin >> n2Read;
    getline(cin, add);
    
    for(int i = 0; i < n2Read; i++){
        getline (cin, add);
        
        one.set(add);
        
        if(one.isEmpty() == false){
            eventS.add(one);
            nEvents++;
        }
    }
    
    cout << "Number of events to read" << endl;
    cout << "The whole EventSet: " << nEvents << endl;

    // 2. Prepare a new eventSet by selecting the purchase Events
    
    EventSet purchaseSet = rawFilterEvents(eventS, "type", "purchase");

    // 3. show the size of the new purchaseSet
    
    cout << "Sales found: " << purchaseSet.size() << endl;
    cout << endl;
    
    // 4. show the distribution for purchase in week days 
    
    int arrayA[7] = {0};
    
    DataVector weeklyData;
    computeActivity(purchaseSet, arrayA);
    
    weeklyData.alloc(7);
    weeklyData.setTitle("Sales/day");
    weeklyData.loadLabels(DAYNAME);
    weeklyData.loadValues(arrayA);
    cout << weeklyData.showFramedReportH(0); // Number od decimal digits
    

    // 5. Find the money spent on every brand which is present in purchaseSet
    
    string val_brands[500]; //Ponemos mucho espacio en el array
    int n_brands = 0;
    
    findUnique(purchaseSet, "Brand", val_brands, n_brands);
    double money[n_brands];
    
    for(int i = 0; i < n_brands; i++){
        aux.clear();
        
        for(int k = 0; k < purchaseSet.size(); k++){
            if(purchaseSet.at(k).getField("Brand") == val_brands[i]){
                aux.add(purchaseSet.at(k));
            }
        }
        
        money[i] = sumPrice(aux);
    }
    
    DataVector brandData;
    
    brandData.alloc(n_brands);
    brandData.setTitle("$/Brand");
    brandData.loadLabels(val_brands);
    brandData.loadValues(money);
    
    if(n_brands > 0){
        cout << brandData.showFramedReportH(2); // Number od decimal digits
    }
    

    // 6. Find the number of sales for every user present in purchaseSet
    string val_users[500];
    int n_users = 0;
    
    findUnique(purchaseSet, "UserID", val_users, n_users);
    int mov_users[n_users];
    int mov = 0;
    
    int users[n_users];
    
    for(int i = 0; i < n_users; i++){
        aux.clear();
        mov = 0;
        
        for(int k = 0; k < purchaseSet.size(); k++){
            if(purchaseSet.at(k).getField("UserID") == val_users[i]){
                mov++;
            }
        }
        
        mov_users[i] = mov;
    }
    
    DataVector usersData;
    
    usersData.alloc(n_users);
    usersData.setTitle("QTY/User");
    usersData.loadLabels(val_users);
    usersData.loadValues(mov_users);
    
    if(n_users > 0){
        cout << usersData.showFramedReportH(0); // Number of decimal digits
    }
    
    

    // Report everything to the integration tests
    REPORT_DATA(eventS);
    REPORT_DATA(purchaseSet);
    REPORT_DATA(weeklyData);
    REPORT_DATA(brandData);
    REPORT_DATA(usersData);
    
    return 0;
}

/*int main(){
    DateTime date;
    EventSet es;  
    Event e, last_event;
    string expected, before, later, mark1=VALID_TYPES[1], mark2=VALID_TYPES[2];
    int count1, count2, count3, position, n1, n2;
    float price;
    string  dt1="2021-02-17 00:00:00 UTC", dt2= "2020-02-29 00:00:00 UTC";
    
    count1=100;
    string res1[count1], res2[count1];
    count2=5;
    count3=25;
    price=0.25;
    for (int i=0; i<count1; i++) {
        if (i<count1/2)
            e.setPrice(price*0.5);
        else
            e.setPrice(price*1.5);
        e.setBrand(((string) "BRAND")+std::to_string(i%count2));
        e.setUserID(((string) "USER")+std::to_string(i%count3));
        es.add(e);
    }
    findUnique(es, "Brand", res1, n1);
    findUnique(es,"UserID", res2,n2);
    
    return 0;
}*/

void computeActivity(const EventSet & evSet, int arrayA[]) {
    for(int i = 0; i < evSet.size(); i++){
        arrayA[evSet.at(i).getDateTime().weekDay()]++;
    }

}


