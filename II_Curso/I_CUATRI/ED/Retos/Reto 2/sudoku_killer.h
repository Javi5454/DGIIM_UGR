/*!
 * @file sudoku_killer.h
 * @brief Cabecera para la clase Sudoku_Killer
 */

#ifndef _SUDOKU_KILLER_
#define _SUDOKU_KILLER_

#include <iostream>

/**
* @brief T.D.A Sudoko Killer
  Una instancia del tipo de dato abstracto Sudoku_Killer nos permite crear sudokus del tipo killer.

  El TDA Sudoku_Killer proporciona además distintas herramientas para conseguir la resolución de dicho sudoku

  Para poder usar el TDA Sudoku_Killer se debe incluir el fichero

  \#include <sudoku_killer.h>

  @author Javier Gómez López
  @date Octubre 2021
*/

class Sudoku_Killer{
    /**
      @page repSudokuKiller Representación del TDA Sudoku_Killer.

      @section invSudokuKiller Invariante de la representación.

      En un sudoku no se debe repetir ninguna cifra en una misma fila, columna o subcuadrícula.

      Para que el sudoku sea de tipo "killer", no debe de haber números iniciales, si no grupos de celdas
      en los cuales se especifica la suma de los números de dichas casillas

      @section faSudokuKiller Función de abstracción

      fa: tipo_rep ----> Sudoku Killer
          int[9][9] ----> sudoku_killer

      La estructura int[9][9] representa al sudoko_killer.
     **/

private:

    /**
        * @brief Matriz 9x9 que contiene el sudoku, por defecto vale 0
      */

    vector<vector<int>> tablero = {{0,0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0,0},
                                   {0,0,0,0,0,0,0,0,0}};

    /**
      *@brief Esta matriz identifica cada celda con un numero único. Dicho número se
      asigna por orden de aparacion de las celdas leyendo el sudoku the izquierda a
      derecha y de arriba a abajo
     */
     vector<vector>int>> celdas;

     /**
       * @brief En est vector, la posición n contiene la suma se la celda cuyo
        número es n
      */

     vector<int> celdas_sum;

     /**
      * @brief Método recursivo que da la suma de una celda dada.
      * Checkeamos las 4 casillas más cercanas a la que se está checkeando y la
      * añadimos recursivamente.
      * @param i Fila casilla
      * @param j Columna casilla
      * @param celda_id  el número de la celda a checkear
      * @param checked matriz para comprobar si hemos checkeado ya una casilla
      * @param result resultado de la función
      * @post Si el proceso falla el resultado es 0
      */
     void getSum(int i, int j, int celda_id, bool checked[9][9], int &result);

     /**
      * @brief Checkea si ese valor aparece ya en la fila donde se quiere colocar
      * @param val Número que se quiere colocar
      * @param row Fila a checkear
      * @return True si está en la fila, false si no está en la fila
      */
     bool alreadyInRow(int val, int row);

     /**
      * @brief Checkea si el valor aparece ya en la columna donde se quiere colocar
      * @param val Número que se quiere colocar
      * @param col Columna a checkear
      * @return True si está en la columna, false si no
      */
     bool alreadyInCol(int val, int col);

     /**
      * @brief Checkea si el número está en una subcaja de 3x3
      * @param row Fila de la caja
      * @param col Columna de la caja
      * @param val Número que se quiere colocar
      * @return True si está en la subcaja, False si no está
      */
     bool alredyInSmallGrid(int row, int col, int val);

     /**
      * @brief Checkea si se puede poner el valor en la posición especificada
      * @param row Fila donde se quiere colocar
      * @param col Columna donde se quiere colocar
      * @param val Número que se quiere colocar
      * @return True si se puede colocar, False si no
      */
     bool canUse(int row, int col, int val);

public:

    /**
     * @brief Constructor con parámetros
     * @param celdas Las celdas enlazadas por las normas killer del sudoku
     * @param celdas_sum La suma de cada una de las celdas
     */
    Sudoku_Killer(vector<vector<int>> celdas, vector<int> celdas_sum);

    /**
     * @brief Imprime el sudoku por un cauce dado
     * @pre dest debe de haberse checkeado
     * @param dest Cauce de destino del sudoku
     * @post El cauce dado tiene el sudoku
     */
    void printSudoku(ofstream dest);

    /**
     * @brief Soluciona el sudoku de manera recursiva
     * @param i Actual fila
     * @param j Actual columna
     * @return True si lo ha solucionado, False si aún no se ha resuelto.
     * @post El sudoku estará resuelto, no se hace por copia.
     */
    bool solveSudoku(int i, int j);

};

#endif // _SUDOKU_KILLER_