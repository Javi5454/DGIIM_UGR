#include <iostream>
#include <fstream>
#include <fstream>
using namespace std;

int nalumnos = 51;
const string _nombres[] = {"JOSE ALGAR FERNANDEZ", "JOAQUIN ARCILA PEREZ", "GERARDO ARENAS NASRAWIN", "CARMEN AZORIN MARTI", "RUBEN BALLESTEROS RIVERO", "MARTA BENITEZ HERNANDEZ", "MANUEL VICENTE BOLAÑOS QUESADA", "CLARA BOLIVAR PELAEZ", "LORENA CACERES ARIAS", "PEDRO HAIMAR CASTILLO GARCIA", "LUCIA CEPEDA GONZALEZ", "MARIA CRIBILLES PEREZ", "MANUEL DIAZ-MECO TERRES", "PABLO GALVEZ ORTIGOSA", "JESUS SAMUEL GARCIA CARBALLO", "CARLOS GARCIA JIMENEZ", "BORA GOKER SOLA", "JAVIER GOMEZ LOPEZ", "ANA GRACIANI DONAIRE", "JOSE ALBERTO HOCES CASTRO", "SHAO JIE HU CHEN", "ADRIAN JAEN FUENTES", "AARON JERONIMO FERNANDEZ", "NOURA LACHHAB BOUHMADI", "LAURA LAZARO SORALUCE", "RAMON LIRIA SANCHEZ", "ENRIQUE LOPEZ GARCIA", "CARLOTA LOPEZ QUESADA", "PAULA MANGANO GONZALEZ", "JOSE MARIA MARTIN MARTIN", "JAIME MARTINEZ BRAVO", "FRANCISCO NICOLAS MEDINA ROSAS", "MARIO MEGIAS MATEO", "JOSE LUIS MERA CARDOSO", "CRISTOBAL MERINO SAEZ", "QUINTIN MESA ROMERO", "ALVARO MOLINA ALVAREZ", "JUAN MOLINA MOLINA", "EDUARDO MOLINA VELAZQUEZ", "CLARA ORTEGA SEVILLA", "CARLOS MANUEL PERALES GOMEZ", "PEDRO PLAZAS MUNUERA", "CARLOS QUESADA PEREZ", "EDUARDO RODRIGUEZ CAO", "TOMAS RODRIGUEZ HERNAEZ", "ELSA RODRIGUEZ MACMICHAEL", "MARIO RUBIO VENZAL", "MANUEL RUIZ AGUILAR", "SOLEDAD RUIZ GOMEZ", "DAVID TORONJO MENDOZA", "ELENA TORRES FERNANDEZ"};

void Introduccion(const string &nombre) {
    int _i, _tipo;
    string aux;
    cout << "Buscando (" << nombre << ")" << endl;
    for (_i = 1; _i <= nalumnos && _nombres[_i - 1] != nombre; _i++);
    if (_i <= nalumnos) {
        cerr << "Alumno: " << nombre << endl;
        cerr << "Fichero: " << "1." + to_string(_i) + ".xhtml" << endl;
        cerr << "Variante: ";
        _tipo = nombre[0] % 4;
        switch (nombre[0] % 4) {
            case 0: cerr << "<class=" << endl;
                break;
            case 1: cerr << "<href=" << endl;
                break;
            case 2: cerr << "<sup>" << endl;
                break;
            case 3: cerr << "<h3>" << endl;
                break;
        }
        cerr << endl << endl << endl;
        //        cout << nombre << " " << _i << " " << _tipo << endl;
    } else {
        cout << "Por favor introduce tu nombre tal y como aparece en el array nombres[] " << endl;
        exit(1);
    }
}

/**
 * @brief Implementa la función del enunciado 
 * @param v1 Primer vector
 * @param nv1 Número de elementos de @a v1
 * @param v3 Vector resultado. Debe reservarse memoria dentro de la función
 * @param nv3 Número de elementos de @a v3
 */
void funcion(string const *v1, int nv1, string * &v3, int &nv3) {
    int appears = 0;
    
    for (int i = 0; i < nv1; i++){
        if(v1[i].find("<sup>") != -1){
            appears++;
        }
    }
    
    nv3 = appears;
    int pos = 0;
    
    v3 = new string [nv3];
    
    for (int i = 0; i < nv1; i++){
        string to_add;
        if(v1[i].find("<sup>") != -1){
            bool keep = true;
            for (int j = v1[i].find("<sup>") + 5; j < v1[i].length() && keep; j++){
                if(v1[i].at(j) != '<'){
                    to_add += v1[i].at(j);
                }
                else{
                    keep = false;
                }
               
            }
         v3[pos] = to_add;
         pos++;
        }
    }
    
}

int main() {
    ifstream findice, ficapitulo;
    ofstream fosalida;
    string nameindice = "./data/index.dat",
            namesalida = "./data/salida.dat",
            namecapitulo = "1.18.xhtml";
    string *capitulo = nullptr, *seleccion = nullptr;
    int ncapitulo, nseleccion;

    string linea, cadena;
    bool salir;

    // Consulta tu nombre, fichero de trabajo y variante
    Introduccion("JAVIER GOMEZ LOPEZ"); // Copia aquí tu nombre
    
    // Abrir fichero de indice. Comprobar sólo error de apertura
    findice.open(nameindice);
    
    if(!findice){
        cout << "Error abriendo fichero " + nameindice << endl;
        return 1;
    }

    // Buscar namecapitulo en el fichero de índce y leer el número de líneas
    string to_check;
    bool keep = true;
    int pos = 0;
    
    while(findice && keep){
        getline(findice, to_check);
        
        pos = to_check.find(namecapitulo);
        
        if(pos != -1){
            keep = false;
        }
    }
    
    
    for (int i = 0; i < pos; i++){
        linea += to_check[i];
    }
    
    ncapitulo = stoi(linea);
    
    findice.close();

    // Reservar memoria para *capitulo
    
    capitulo = new string [ncapitulo];
    
    // Abrir fichero namecapitulo dentro de "./data/"
    ficapitulo.open("./data/" + namecapitulo);
    
    if(!ficapitulo){
        cout << "Error abriendo fichero " + namecapitulo << endl;
        delete [] capitulo;
        capitulo = nullptr;
        return 1;
    }

    // Leer las líneas en memoria dinámica
    int i = 0;
    for (i = 0; i < ncapitulo && ficapitulo; i++){
        getline(ficapitulo, capitulo[i]);
    }
    
    if(i < ncapitulo){
        cout << "Error de datos en " << namecapitulo << endl;
        delete [] capitulo;
        capitulo = nullptr;
        return 1;
    }
    
    ficapitulo.close();
    
    // Calcular la lista de cadenas de la variante
    funcion(capitulo, ncapitulo, seleccion, nseleccion);
    
    
    // Guardar el resultado en "./data/salida.dat"
    fosalida.open("./data/salida.dat");
    
    if (!fosalida){
        cout << "Error abriendo fichero ./data/salida.dat" << endl;
        
        delete [] capitulo;
        capitulo = nullptr;
        
        delete [] seleccion;
        seleccion = nullptr;
        
        return 1;
    }
    
    for (int i = 0; i < nseleccion; i++){
        fosalida << seleccion[i] << endl;
    }
    
    fosalida.close();

    // Liberar la memoria
    delete [] capitulo;
    capitulo = nullptr;
    
    delete [] seleccion;
    seleccion = nullptr;
    return 0;
}