/* 
 * File:   matrix.cpp
 * Author: MP-team 
 * @warning To be implemented by students. Follow the instructions given in the headers
 */


#include "Matrix.h"
#include <fstream>
#include <assert.h>
#include "DataVector.h"

using namespace std;
double negative = -1;

/**
 * @brief Copies the values in a 2D matrix org with nrows and ncols to an also 2D matrix dest.
 * It is assumed that org and dest have the memory properly allocated 
 * @param dest destination matrix
 * @param org  source matrix
 * @param nrows number of rows
 * @param ncols number of cols
 */
void copy(double **dest, double **org, size_t nrows, size_t ncols) {
    
    if(org != nullptr){
        for(int i = 0; i < nrows; i++){
            for (int j = 0; j < ncols; j++){
                dest[i][j] = org[i][j];
            }
        }
    }
    else{
        dest = nullptr;
    }
    
        

}

/** 
 * @brief this method reserve memory to allocate a 2D matrix of size r x c.
 * @param r number of rows
 * @param c number of cols
 * @return the pointer to the memory block containing the data
 */
double ** allocate(size_t r, size_t c) {
    double ** block;
    
    block = new double* [r];
    
    for (int i = 0; i < r; i++){
        block[i] = new double [c];
    }
    
    return block;
}

/**
 * @brief In this method, given an index idx it returns the key in the position i, 
 * such that i is the first position in the index such that idx.at(i).getPos()==p
 * @param idx the input index
 * @param p number of 
 * @return the key for first position i in the index such that idx.at(i).getPos()==p
 */
string labelWithValuePosInIndex(const Index & idx, size_t p) {
    string salida;

    bool enc = false;
    for (int i = 0; i < idx.size() && !enc; i++) {
        if (idx.at(i).getPos() == p) {
            salida = idx.at(i).getKey();
            enc = true;
        }
    }
    return salida;
}

void Matrix::deallocate() {
    if(_data != nullptr){
        for(int i = 0; i < _nrows; i++){
            delete [] _data[i];
        }
    }
    
    delete [] _data;
    _data = nullptr;
}


Matrix::Matrix() {
   _data = nullptr;
   Index null;
   
   _rowLabels = null;
   _colLabels = null;
   
   _nrows = 0;
   _ncols = 0;
}

void Matrix::setValues(double valor) {
    for(int i= 0; i < _nrows; i++){
        for (int j = 0; j < _ncols; j++){
            _data[i][j]=valor;
        }
    }
}



Matrix::Matrix(size_t f, size_t c, double vdef) {
    
    if(f >= 1 && c >= 1){
        _data = allocate(f,c);
        _nrows = f;
        _ncols = c;

        setValues(vdef);
        
        Index null;
   
        _rowLabels = null;
        _colLabels = null;
    }
    else{
        Matrix();
    }
}

Matrix::Matrix(const Matrix& orig) {
    _data = allocate(orig._nrows, orig._ncols);
    _nrows = orig.rows();
    _ncols = orig.columns();
    
    
    copy(_data, orig._data, orig._nrows, orig._ncols);
    
    _rowLabels = orig._rowLabels;
    _colLabels = orig._colLabels;
    
}

Matrix::Matrix(const std::string *rowLabels, size_t nrows, const std::string * colsLabels, size_t ncols, double value) {
    if(nrows >= 1 && ncols >= 1){
        _data = allocate(nrows,ncols);
        _nrows = nrows;
        _ncols = ncols;

        setValues(value);
        
        Index rows;
    
    for(int i = 0; i < nrows; i++){
        Pair to_add(rowLabels[i],i);
        
        rows.add(to_add);
    }
    
    _rowLabels = rows;
    
    Index cols;
    
    for(int i = 0; i < ncols; i++){
        Pair to_add(colsLabels[i],i);
        
        cols.add(to_add);
    }
    
    _colLabels = cols;
    }
    else{
        Matrix();
    }
    
}



std::string Matrix::labelAtRow(size_t row) const {
    return labelWithValuePosInIndex(_rowLabels, row);
}

std::string Matrix::labelAtCol(size_t col) const {
    return labelWithValuePosInIndex(_colLabels, col);
}

void Matrix::resize(size_t nrows, size_t ncols, double value) {
    deallocate();
    
    if(nrows >= 1 && ncols >= 1){
        _data = allocate(nrows,ncols);
        _nrows = nrows;
        _ncols = ncols;

        setValues(value);
        
        Index null;
   
        _rowLabels = null;
        _colLabels = null;
    }
}

void Matrix::resize(const std::string * rowLabels, size_t nrows, const std::string * colLabels, size_t ncols, double value) {
    resize(nrows, ncols, value);
    
    Index rows;

    for(int i = 0; i < nrows; i++){
        Pair to_add(rowLabels[i],i);

        rows.add(to_add);
    }

    _rowLabels = rows;

    Index cols;

    for(int i = 0; i < ncols; i++){
        Pair to_add(colLabels[i],i);

        cols.add(to_add);
    }

    _colLabels = cols;
}

void Matrix::clear() {
    deallocate();
    
    Index null;
    
    _rowLabels = null;
    _colLabels = null;
    
    _nrows = 0;
    _ncols = 0;
}

Matrix::~Matrix() {
    deallocate();
    _nrows = 0;
    _ncols = 0;
}

double & Matrix::at(size_t f, size_t c) {
    if(f < _nrows && c < _ncols && f >= 0 && c >= 0){
        return _data[f][c];
    }
    else{
        return negative;
    }
}

const double & Matrix::at(size_t f, size_t c) const {
    
    if(f < _nrows && c < _ncols && f >= 0 && c >= 0){
        return _data[f][c];
    }
    else{
        return negative;
    }
}

double & Matrix::operator()(size_t f, size_t c) {
    return at(f,c);
}

const double & Matrix::operator()(size_t f, size_t c) const {
    return at(f,c);
}

int Matrix::rowIndexOf(const std::string & label) const {
    bool keep = true;
    int result = npos;
    
    for (int i = 0; i < _nrows & keep; i++){
        if(label == _rowLabels.at(i).getKey()){
            result = i;
            keep = false;
        }
    }
    
    return result;
}

int Matrix::colIndexOf(const std::string & label) const {
    bool keep = true;
    int result = npos;
    
    for (int i = 0; i < _ncols & keep; i++){
        if (label == _colLabels.at(i).getKey()){
            result = i;
            keep = false;
        }
    }
    
    return result;
}

double & Matrix::at(const std::string & rowLabel, const std::string & colLabel) {
    int row = rowIndexOf(rowLabel);
    int col = colIndexOf(colLabel);
    
    return at(row, col);
}

double & Matrix::operator()(const std::string & rowLabel, const std::string & colLabel) {
    return at(rowLabel,colLabel);
}

const double & Matrix::at(const std::string & rowLabel, const std::string & colLabel)const {
    int row = rowIndexOf(rowLabel);
    int col = colIndexOf(colLabel);
    
    return at(row, col);
}

const double & Matrix::operator()(const std::string & rowLabel, const std::string & colLabel)const {
    return at(rowLabel, colLabel);
}

ostream & operator<<(ostream & flujo, const Matrix& m) {
    flujo << m.rows() << " " << m.columns() << endl;
    
    bool labeled = (m._rowLabels.size() != 0);
    
    if(labeled){
        for(int i = 0; i < m.rows(); i++){
            flujo << m.labelAtRow(i) << " ";
        }
        
        flujo << endl;
        
        for (int i = 0; i < m.columns(); i++){
            flujo << m.labelAtCol(i) << " ";
        }
        
        flujo << endl;
    }
    
    for (int i = 0; i < m.rows(); i++){
        for (int j = 0; j < m.columns(); j++){
            flujo << m(i,j) << " ";
        }
            flujo << endl;
        
    }
    
    return flujo;
}

Matrix & Matrix::operator=(const Matrix& m) {
    if(this!=&m){
        deallocate();
        this->_nrows = m._nrows;
        this->_ncols = m._ncols;
        this->_rowLabels = m._rowLabels;
        this->_colLabels = m._colLabels;
        this->_data = allocate(_nrows,_ncols);
        copy(this->_data, m._data, m._nrows, m._ncols);
    }
    
    return *this;
}

void Matrix::setLabels(Index & idx, const string * labels, int nlabels){
     idx.clear();
    int lb,ub;
    bool correct = true;
    for (int i=0; i< nlabels && correct; i++){
        lb = idx.lower_bound(labels[i]);
        ub = idx.upper_bound(labels[i]);
        if (lb==ub) { // it is NOT in the set
            idx.add(Pair(labels[i],i));
        } else {
            correct = false;
         }
    }
    if (!correct) idx.clear();
 }

int Matrix::getLabels(const Index & idx, string * labels) const {
    if (idx.size() > 0) {
        for (int i = 0; i < idx.size(); i++) {
            labels[i] = idx.at(i).getKey();
        }
    }
    return idx.size();
}

int Matrix::getRowLabels(string * labels) const {
    return getLabels(_rowLabels,labels);
}

int Matrix::getColLabels(string *labels) const {
    return getLabels(_colLabels,labels);
}

size_t Matrix::columns() const {
    return _ncols;
}

size_t Matrix::rows() const {
    return _nrows;
}

//uncomment
void Matrix::save(const string & nf) const{
    ofstream fsal(nf);
    if (fsal.is_open()) {
        fsal << "#matrix "; 
        if (_rowLabels.size()==0)
            fsal << "unlabeled"<< endl;
        else fsal << "labeled" << endl;
        fsal << *this;
        fsal.close();
    } else cerr << "Fail creating " << nf << " file" <<endl;
}

void Matrix::load(const string & nf) {
    ifstream fent(nf);
    string labeled, cad;
    clear();
    if (fent.is_open()) {
         fent >> cad >> labeled;
         fent >> _nrows >> _ncols;
         if (labeled == "labeled"){
            for (int i=0;i<_nrows;i++){
                fent >> cad;
                _rowLabels.add(Pair(cad,i));
            }
             for (int i=0;i<_ncols;i++){
                fent >> cad;
                _colLabels.add(Pair(cad,i));
            }
        }
        _data = allocate(_nrows,_ncols); 
        for (int i = 0; i < _nrows; i++) {
            for (int j = 0; j < _ncols; j++) {
                fent >> _data[i][j];
            }
        }
        fent.close();
    } else cerr << "Fail reading " << nf << " file" <<endl;
}

Matrix & Matrix::operator*=(double val) {
    for(int i = 0; i < this->_nrows; i++){
        for(int j = 0; j< this->_ncols; j++){
            this->_data[i][j] = this->_data[i][j] * val;
        }
    }
    
    return *this;
}

Matrix & Matrix::operator+=(double val) {
    for(int i = 0; i < this->_nrows; i++){
        for(int j = 0; j < this->_ncols; j++){
           this->_data[i][j] = this->_data[i][j] + val; 
        }
    }
    
    return *this;
}

Matrix Matrix::operator*(const Matrix & m) const {
    Matrix result(this->_nrows, m.columns());
    
    if(this->_ncols == m.rows()){

        for(int i = 0; i < this->_nrows; i++){
            for(int j = 0; j < m.columns(); j++){
                double aux = 0;
                for(int k = 0; k < this->_ncols; k++){
                    aux += this->_data[i][k] * m(k,j);
                }
                result._data[i][j] = aux;
            }
        }
    }
    else{
        result.setValues(npos);
    }
    
    result._colLabels = m._colLabels;
    result._rowLabels = m._rowLabels;
    
    return result;
}

Matrix Matrix::operator+(double val) const {
    Matrix result(this->_nrows, this->_ncols);
    
    for(int i = 0; i < this->_nrows; i++){
        for(int j = 0; j < this->_ncols; j++)
            result._data[i][j] = this->_data[i][j] + val;
    }
    
    return result;
}

Matrix Matrix::operator*(double val) const {
    
    Matrix result(this->_nrows, this->_ncols);
    for(int i = 0; i < this->_nrows; i++){
        for(int j = 0; j < this->_ncols; j++){
            result._data[i][j] = this->_data[i][j] * val;
        }
    }
    
    result._colLabels = this->_colLabels;
    result._rowLabels = this->_rowLabels;
    
    return result;
}

Matrix operator+(double ival, const Matrix & dch) {
    Matrix result(dch.rows(), dch.columns());
    
    result = dch + ival;
    
    return result;
    
}

Matrix operator*(double ival, const Matrix & dch) {
    Matrix result(dch.rows(), dch.columns());
    
    result = dch * ival;
    
    return result;
}

Matrix & Matrix::normalize(){
    double sum[_nrows] = {0};
    
    for(int i = 0; i < _nrows; i++){
        for(int j = 0; j < _ncols; j++){
            sum[i] += _data[i][j];
        }
    }
    
    for (int i = 0; i < _nrows; i++){
        for (int j = 0; j < _ncols; j++){
            if(sum[i] != 0){
                _data[i][j] = _data[i][j] / sum[i];
            }
            else{
                _data [i][j] = 1 / _nrows;
            }
        }
    }
    
    return *this;
}
