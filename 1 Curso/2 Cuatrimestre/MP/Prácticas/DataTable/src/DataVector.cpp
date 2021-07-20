/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <cassert>
#include <cmath>
#include "AnsiTerminal.h"
#include "DataVector.h"
#include "datatools.h"
using namespace std;

const std::string SPECIAL_CHARS[] = {"┌┐└┘─│┬┴┼┤├▄", "++++-|", "▁▂▃▄▅▆▇█", "▏▎▍▌▋▊▉█"};

#define MAXCANVAS(d) (max(d)*1.25)
#define MAXSKIP (d) ((d)<=1? 1 : (d)<=5 ? 5: (d)<=10? 10 :(d) <=25 ? 25: 100)
#define WIDTH 175
#define HEIGHT 75
AnsiTerminal DataVector::_term(WIDTH, HEIGHT);
int DataVector::nreports = 0;
int DataVector::_x = 1;
int DataVector::_y = 1;

double maxSkip(double d) {
    if (d <= 1)
        return 1;
    else if (d <= 5)
        return 5;
    else if (d <= 10)
        return 10;
    else if (d <= 25)
        return 25;
    else if (d <= 100)
        return 100;
    else
        return 1000;
}

double max(const DataVector &dv) {
    double s = dv.getValue(0);
    for (int i = 0; i < dv.size(); i++) {
        s = (s < dv.getValue(i) ? dv.getValue(i) : s);
    }
    return s;
}

double min(const DataVector &dv) {
    double s = dv.getValue(0);
    for (int i = 0; i < dv.size(); i++) {
        s = (s > dv.getValue(i) ? dv.getValue(i) : s);
    }
    return s;
}

double sum(const DataVector &dv) {
    double s = 0;
    for (int i = 0; i < dv.size(); i++) {
        s += dv.getValue(i);
    }
    return s;
}

double average(const DataVector &dv) {
    return sum(dv) / dv.size();
}

DataVector::DataVector() {
    clear();
}

DataVector::DataVector(int ndata) {
    clear();
    alloc(ndata);
}

DataVector::~DataVector() {
    nreports--;
    if (nreports < 1) {
        _term.close();
    }
}

DataVector & DataVector::clear() {
    _title = "";
    _nData = 0;
    _width = WIDTH;
    _height = 15;
    for (int i = 0; i < MAX_WIDTH; i++) {
        _data[i] = 0;
        _labels[i] = "";
    }
    if (nreports < 1) {
        _x = 1;
        _y = 1;
        _term.setMain().clearScreen();
    }
    nreports++;
    return *this;
}

DataVector & DataVector::alloc(int n) {
    clear();
    _nData = n;
    return *this;
}

int DataVector::size() const {
    return _nData;
}

double DataVector::getValue(int pos) const {
    assert(0 <= pos && pos < size());
    return _data[pos];
}

string DataVector::getLabel(int pos) const {
    assert(0 <= pos && pos < size());
    return _labels[pos];
}

DataVector &DataVector::setValue(int pos, double data) {
    assert(0 <= pos && pos < size());
    _data[pos] = data;
    return *this;
}

DataVector &DataVector::setLabel(int pos, const string & label) {
    assert(0 <= pos && pos < size());
    _labels[pos] = label;
    return *this;
}

DataVector & DataVector::loadValues(const int values[]) {
    for (int i = 0; i < size(); i++)
        setValue(i, values[i]);
    return *this;
}

DataVector & DataVector::loadValues(const double values[]) {
    for (int i = 0; i < size(); i++)
        setValue(i, values[i]);
    return *this;
}

DataVector & DataVector::loadLabels(const std::string labels[]) {
    for (int i = 0; i < size(); i++)
        setLabel(i, labels[i]);
    return *this;
}

DataVector & DataVector::loadLabels(const char* const labels[]) {
    for (int i = 0; i < size(); i++)
        setLabel(i, labels[i]);
    return *this;
}

DataVector & DataVector::add(const string &label, double data) {
    assert(_nData < MAX_WIDTH);
    _labels[_nData] = label;
    _data[_nData++] = data;
    return *this;
}

DataVector & DataVector::setTitle(const string &title) {
    _title = title;
    return *this;
}

string DataVector::showPlainReportH(int decpos) {
    string res = _title + "\n",
            fdata = (string) "%" + std::to_string(FIELD_WIDTH) + "." + std::to_string(decpos) + "f",
            flabel = (string) "%" + std::to_string(FIELD_WIDTH) + "s",
            axis = "";
    double byrow;
    char aux [MAX_WIDTH];
    for (int i = 0; i < FIELD_WIDTH; i++)
        axis = axis + "─";
    byrow = 0;
    for (int i = 0; i < size(); i++) {
        sprintf(aux, fdata.c_str(), getValue(i));
        res = res + aux ;
        byrow += getValue(i);
    }
    sprintf(aux, fdata.c_str(), byrow);
    res = res + aux + "\n";
    res += "\n";
    for (int i = 0; i < size(); i++) {
        string f = (string) "%" + STR(FIELD_WIDTH) + "s";
        res = res + format(f, trim(getLabel(i).c_str(), ANSI_FIELD_LENGTH + 5));
    }
    res += "\n";
    if (this->_nData >= 20) {
        res = this->showPlainReportV(decpos);
    }
    return res;
}

string DataVector::showFramedReportH(int decpos) {
    string res = _title + "\n",
            fdata = (string) "%" + std::to_string(FIELD_WIDTH) + "." + std::to_string(decpos) + "f",
            flabel = (string) "%" + std::to_string(FIELD_WIDTH) + "s",
            axis = "";
    double byrow;
    char aux [MAX_WIDTH];
    for (int i = 0; i < FIELD_WIDTH; i++)
        axis = axis + "─";
    byrow = 0;
    res += "┌";
    for (int i = 0; i < size(); i++) {
        res = res + axis;
        if (i < size() - 1)
            res += "┬";
    }
    res += "┐\n│";
    for (int i = 0; i < size(); i++) {
        sprintf(aux, fdata.c_str(), getValue(i));
        res = res + aux + "│";
        byrow += getValue(i);
    }
    sprintf(aux, fdata.c_str(), byrow);
    res = res + aux + "\n";
    res += "├";
    for (int i = 0; i < size(); i++) {
        res = res + axis;
        if (i < size() - 1)
            res += "┼";
    }
    res += "┤\n│";
    for (int i = 0; i < size(); i++) {
        string f = (string) "%" + STR(FIELD_WIDTH) + "s";
        res = res + format(f, trim(getLabel(i).c_str(), ANSI_FIELD_LENGTH + 5)) + "│";
    }
    res += "\n└";
    for (int i = 0; i < size(); i++) {
        res = res + axis;
        if (i < size() - 1)
            res += "┴";
    }
    res += "┘\n";
    if (this->_nData >= 20) {
        res = this->showFramedReportV(decpos);
    }
    return res;
}


string DataVector::showFancyReportH(int decpos) {
    if (this->_nData >= 32) {
        return this->showFancyReportV(decpos);
    }
    _term.openWindow();
    string f = (string) "%" + std::to_string(ANSI_FIELD_LENGTH) + "." + std::to_string(decpos) + "f";
    _term.setCursorOff();
    _term.setCanvas();
    string stitle = _title;
    _title = _title + " (" + format(f, sum(*this)) + ") ";
    decorate("base").decorate("portrait");
    _title = stitle;
    _term.setCanvas();
    for (int i = 0; i < size(); i++) {
        double rh = getValue(i) / _ratioy;
        int x = _canvasx + (i + 1) * _ratiox,
                y;
        y = _canvasy + _canvash - 1;
        _term.setCanvas();
        string label = format(f, getValue(i));
        _term.setText(_term.pal[i % 15]);
        for (int b = 0; b < _ratiox; b++) {
            _term.printMinibarV(x - _ratiox / 2 + b, y, _canvash, MAXCANVAS(*this), getValue(i));
        }
        if (_ratiox > 3) {
            _term.setCanvas();
            _term.setCursorXY(x - label.length() / 2, y - rh - 1).print(label);
        }
    }
    _term.setCursorXY(_x, _y + _height);
    _term.setCursorOn();
    _y += _height;
//    return _term.to_string();
    return showFramedReportV();
}


string DataVector::showPlainReportV(int decpos) {
    string res = _title + "\n",
            fdata = (string) "%" + std::to_string(FIELD_WIDTH) + "." + std::to_string(decpos) + "f",
            flabel = (string) "%" + std::to_string(FIELD_WIDTH) + "s",
            axis = "";
    double byrow;
    char aux [MAX_WIDTH];
    int i;

    byrow = 0;
    for (int i = 0; i < size(); i++) {
        res = res + format(flabel.c_str(), trim(getLabel(i).c_str(), FIELD_WIDTH));
        sprintf(aux, fdata.c_str(), getValue(i));
        res = res + aux;
        byrow += getValue(i);
        res += "\n";
    }
    res += "\n";
    sprintf(aux, flabel.c_str(), "");
    res = res + aux + " ";
    sprintf(aux, fdata.c_str(), byrow);
    res = res + aux + "\n";
    return res;
}

string DataVector::showFramedReportV(int decpos) {
    string res = _title + "\n",
            fdata = (string) "%" + std::to_string(FIELD_WIDTH) + "." + std::to_string(decpos) + "f",
            flabel = (string) "%" + std::to_string(FIELD_WIDTH) + "s",
            axis = "";
    double byrow;
    char aux [MAX_WIDTH];
    int i;

    byrow = 0;
    for (int i = 0; i < FIELD_WIDTH; i++)
        axis = axis + "─";
    res += "┌";
    for (int i = 0; i < 2; i++) {
        res = res + axis;
        if (i < 1)
            res += "┬";
    }
    res += "┐\n│";
    for (int i = 0; i < size(); i++) {
        //sprintf(aux, flabel.c_str(), _labels[i].c_str());
        //string f = (string) "%" + STR(FIELD_WIDTH) + "s";
        res = res + format(flabel.c_str(), trim(getLabel(i).c_str(), FIELD_WIDTH)) + "│";
        sprintf(aux, fdata.c_str(), getValue(i));
        res = res + aux + "│";
        byrow += getValue(i);
        res += "\n";
        if (i < size() - 1) {
            res += "├";
            for (int j = 0; j < 2; j++) {
                res = res + axis;
                if (j < 1)
                    res += "┼";
            }
            res += "┤\n│";
        }
    }
    res += "└";
    for (int i = 0; i < 2; i++) {
        res = res + axis;
        if (i < 1)
            res += "┴";
    }
    res += "┘\n";
    sprintf(aux, flabel.c_str(), "");
    res = res + aux + " ";
    sprintf(aux, fdata.c_str(), byrow);
    res = res + aux + "\n";
    return res;
}


string DataVector::showFancyReportV(int decpos) {
    _term.openWindow();

    string f = (string) "%" + std::to_string(ANSI_FIELD_LENGTH) + "." + std::to_string(decpos) + "f";
    _term.setCursorOff();
    _term.setCanvas();
    string stitle = _title;
    _title = _title + " (" + format(f, sum(*this)) + ") ";
    _height = size() + 5;
    decorate("base").decorate("landscape");
    _title = stitle;
    _term.setCanvas();
    for (int i = 0; i < size(); i++) {
        int rh = (int) std::round(getValue(i) / _ratiox), y = _canvasy + _canvash - 3,
                x;
        x = _canvasx + ANSI_FIELD_LENGTH + 1;
        _term.setCanvas();
        string label = format(f, getValue(i));
        _term.setText(_term.pal[i % 15]);
        _term.printMinibarH(x, y - i, _canvasw - ANSI_FIELD_LENGTH - 2, MAXCANVAS(*this), MAXCANVAS(*this)); // getValue(i));
        _term.setCanvas();
        _term.setCursorXY(x + rh + 2, y - i).print(label);
    }
    _term.setCursorXY(_x, _y + _height);
    _term.setCursorOn();
    _y += _height;
    return showFramedReportV(decpos);
}


DataVector & DataVector::decorate(std::string what) {
    _term.setCursorOff();
    if (what == "base") {
        _term.setMain().setCursorOff();
        _term.doFrameTitle(_title, _x, _y, _width, _height);
        _canvasx = _x + ANSI_FIELD_LENGTH + 2;
        _canvasy = _y + 1;
        _canvasw = _width - 3 - ANSI_FIELD_LENGTH;
        _canvash = _height - 4;
        _term.setCursorXY(_x, _y).setCursorOn();
        for (int h=0; h< _height*2; h++) 
            _term.println("");
        _term.setCanvas().doRectangle(_x + 1, _y + 1, _width - 2, _height - 2);
        _term.setMain();
    }
    if (what == "portrait") {
        _term.setCanvas();
        _ratioy = _term.printVRuler(_canvasx - 1, _canvasy, _canvash, MAXCANVAS(*this), maxSkip(MAXCANVAS(*this) / _canvash));
        _ratiox = _term.printHRuler(_canvasx - 1, _canvasy + _canvash - 1, _canvasw, size() + 1, _labels);
        _term.setMain();
    }
    if (what == "landscape") {
        _term.setCanvas();
        _ratioy = _term.printVRuler(_canvasx - 1, _canvasy, _canvash, size() + 1, _labels);
        _ratiox = _term.printHRuler(_canvasx - 1, _canvasy + _canvash - 1, _canvasw + 1, MAXCANVAS(*this), maxSkip(MAXCANVAS(*this) / _canvasw));
        _term.setMain();
    }
    _term.setCursorOn();
    return *this;
}

