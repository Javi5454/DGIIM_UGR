/**
 * 
PI en paralelo con integración numérica. 
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#ifndef MPI
  #define MPI 3.14159265358979323846
#endif

/**
 * @file  pi.c 
 * @brief PI secuencial con integración numérica, área de rectángulos
 * @author Mancia Anguita
 *  
 * **Compilación**
 * @code
 *  gcc -O2 pi.c -o pi
 * @endcode
 * 
 *  **Ejecución**
 * ~~~~~~~~~~~~~~~~~~~~~
 * ./pi   1000000    (1000000 intervalos de integración)
 * ~~~~~~~~~~~~~~~~~~~~~
 * 
*/
int main(int argc, char **argv)
{
  register double width;
  double sum;
  register int intervals, i; 
  double t0 = 0, t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = 0, t6 = 0, t7 = 0; //para tiempo
    
  //Los procesos calculan PI en paralelo

  // Comprobación de argumentos
  if (argc<2) {
    printf("Falta número de intervalos");
    exit(-1);
  }

  intervals=atoi(argv[1]); 

  if (intervals<1) {
    intervals=1E6; 
    printf("Intervalos=%d",intervals);
  }

  width = 1.0 / intervals;
  sum = 0;
  
t1 = omp_get_wtime();

#pragma omp target enter data map(alloc: width, intervals, sum)

t2 = omp_get_wtime();

#pragma omp target teams distribute parallel for reduction(+:sum) 
  for (i=0; i<intervals; i++) {
    register double x = (i + 0.5) * width;
    sum += 4.0 / (1.0 + x * x);
  }

sum *= width;

t3 = omp_get_wtime();

#pragma omp target exit data map(delete: width) map(from: intervals, sum)

t4 = omp_get_wtime();

  printf(" Iteraciones:\t%d\n PI:\t%26.24f\n Error de cálculo:\t%8.6f\n", intervals,sum,fabs(sum-MPI));

  printf(" Tiempo de transferencia hacia GPU:\t%8.6f\n", t2-t1);
  printf(" Tiempo de cálculo de PI:\t%8.6f\n", t3-t2);
  printf(" Tiempo de transferencia desde GPU:\t%8.6f\n", t4-t3);

  return(0);
}