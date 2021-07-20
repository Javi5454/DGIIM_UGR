/**
 * @file Event.cpp
 * @author DECSAI
 * @note To be implemented by students 
 * 
 */

#include <string>
#include <fstream>
#include "Event.h"
using namespace std;

Event::Event() {
    initDefault();
}

void Event::initDefault() {
    set(EVENT_DEFAULT);
}

Event::Event(const string &line) {
    set(line);
}

DateTime Event::getDateTime()  const{
    return _dateTime;
}

string Event::getType()  const{
    return _type;
}

string Event::getProductID()  const{
    return _prod_id;
}

string Event::getCategoryID()  const{
    return _cat_id;
}

string Event::getCategoryCode()  const{
    return _cat_cod;
}

string Event::getBrand()  const{
    return _brand;
}

double Event::getPrice()  const{
    return _price;
}

string Event::getUserID()  const{
    return _user_id;
}

string Event::getSession()  const{
    return _session;
}

void Event::setDateTime(const string &time) {
    _dateTime.set(time);
}

void Event::setType(const std::string  &type) {
    
    for(int i = 0; i < 4; i++){  //4 es el número de elementos de VALID_TYPES[]
        if(type == VALID_TYPES[i])
        {
            _type = type;
            i = 4;
        }
        else
        {
            _type = VALID_TYPES[0]; //Iniciamos en el tipo por defecto
        }
    }
}

void Event::setProductID(const std::string  &prod_id) {
    
    if(prod_id == "")
    {
        _prod_id = EMPTY_FIELD;
    }
    else
    {
        _prod_id = prod_id;
    }
 }

void Event::setCategoryID(const std::string  &cat_id) {
    _cat_id = cat_id;
}

void Event::setCategoryCode(const std::string  &cat_cod) {
    _cat_cod = cat_cod;
}

void Event::setBrand(const std::string  &brand) {
    _brand = brand;
}

void Event::setPrice(const double &price) {
    if(price >= 0)
    {
        _price = price;
    }
    else
    {
        _price = -1.000000;
    }
}

void Event::setUserID(const std::string  &user_id) {
    if(user_id == " ")
    {
        _user_id = EMPTY_FIELD;
    }
    else
    {
        _user_id = user_id;
    }

}

void Event::setSession(const std::string  &session) {
    if(session == " ")
    {
        _session = EMPTY_FIELD;
    }
    else
    {
        _session = session;
    }

}

void Event::set(const std::string &line) {
    
    string date, type, prod_id, cat_id, cat_cod, brand, price, user_id, session;
    int pos = 0;
    
    for (int i = pos; (line[i] != ',') && (i < line.length()); i ++)
    {
        date += line[i];
        pos++;
    }
    
    setDateTime(date);
    pos++;
    
    for (int i = pos; (line[i] != ',') && (i < line.length()); i ++)
    {
        type += line[i];
        pos++;
    }
    
    setType(type);
    pos++;
    
    for (int i = pos; (line[i] != ',') && (i < line.length()); i ++)
    {
        prod_id += line[i];
        pos++;
    }
    
    setProductID(prod_id);
    pos++;
    
    for (int i = pos; (line[i] != ',') && (i < line.length()); i ++)
    {
        cat_id += line[i];
        pos++;
    }
    
    setCategoryID(cat_id);
    pos++;
    
    for (int i = pos; (line[i] != ',') && (i < line.length()); i ++)
    {
        cat_cod += line[i];
        pos++;
    }
    
    setCategoryCode(cat_cod);
    pos++;
    
    for (int i = pos; (line[i] != ',') && (i < line.length()); i ++)
    {
        brand += line[i];
        pos++;
    }
    
    setBrand(brand);
    pos++;
    
    for (int i = pos; (line[i] != ',') && (i < line.length()); i ++)
    {
        price += line[i];
        pos++;
    }
    
    setPrice(stod(price));
    pos++;
    
    for (int i = pos; (line[i] != ',') && (i < line.length()); i ++)
    {
        user_id += line[i];
        pos++;
    }
    
    setUserID(user_id);
    pos++;
    
    for (int i = pos; (line[i] != ',') && (i < line.length()); i ++)
    {
        session += line[i];
        pos++;
    }
    
    setSession(session);

}

bool Event::isEmpty()  const {
    
    bool resultado = false;
    
    if(getProductID() == EMPTY_FIELD)
    {
        resultado = true;
    }
    else if (getUserID() == EMPTY_FIELD)
    {
        resultado = true;
    }
    else if (getSession() == EMPTY_FIELD)
    {
        resultado = true;
    }
    
    return resultado;

}

string Event::to_string() const {
    string salida;
    salida += _dateTime.to_string();
    salida += "," + _type;
    salida += "," + _prod_id;
    salida += "," + _cat_id;
    salida += "," + _cat_cod;
    salida += "," + _brand;
    salida += "," + std::to_string(_price);
    salida += "," + _user_id;
    salida += "," + _session;
    return salida;
}

std::string Event::getField(const std::string &field) const{
    if(field == "DateTime"){
        return _dateTime.to_string();
    }
    else if (field == "Type"){
        return _type;
    }
    else if (field == "ProductID"){
        return _prod_id;
    }
    else if (field == "CategoryID"){
        return _cat_id;
    }
    else if (field == "CategoryCode"){
        return _cat_cod;
    }
    else if (field == "Brand"){
        return _brand;
    }
    else if (field == "Price"){
        return std::to_string(_price);
    }
    else if (field == "UserID"){
        return _user_id;
    }
    else if (field == "Session"){
        return _session;
    }
    else{
        return "";
    }
}


void Event::write(ostream &os) const { 
    os << to_string() << endl;
}
void Event::read(istream &is) { 
    string line;
    
    getline(is,line);
    
    if(is){
        set(line);
    }
}