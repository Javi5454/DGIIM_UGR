// gcc -Og JGL_Bomba_2021.c -o bombajaviergomez -no-pie -fno-guess-branch-probability

#include <stdio.h> // printf(),fgets(), scanf()
#include <stdlib.h> // exit()
#include <string.h> //strncmp()
#include <sys/time.h> // gettimeofday(), struct timeval

#define SIZE 100
#define TLIM 10
#define MAXSIZE 100

char password[]="mambaout\n"; //contrasenia
int pin = 2804;

void credits(){ //Muestra el autor de la bomba
    printf("\n Bomba por Javier Gómez López\n");
    printf("    @javi5454 - github.com/Javi5454\n");
    printf("    2º DGIIM 2021/2022, UGR\n");
}

void boom(void){ // Imprime BOOM! si no se adivina la contraseña o se acaba el tiempo
    printf("\n"
           "***************\n"
           "*** BOOM!!! ***\n"
           "***************\n"
           "\n");  

           credits();

    exit(-1);
}

void defused(void){ //Imprime bomba desactivada si se desactiva la bomba
    printf("\n"
           "·························\n"
           "··· bomba desactivada ···\n"
           "·························\n"
           "\n");

           credits();

    exit(0);
}

int distract(int n){ //Función de distracion, no tiene utilidad real

    int seguir = 0;

    int i = 0;

    while(i < 10 && seguir == 0){
        i++;
    }

    return n;
}

int mod_pass(void){

    for (size_t i = 0; i < 10; i++)
    {
        int j = 0;
    }
    
    return 16;
}

int main(){
    char password[]="estoestrivial\n";
    int code;
    struct timeval tv1, tv2;

    int enter_code;
    char enter_password[MAXSIZE];
    
    int distraction;

    gettimeofday(&tv1, NULL);

    printf("Rápido, tienes 10 segundos, inserta la ");

    if(distract(distraction) == distraction){
        printf("clave: ");
    }

    scanf("%i", &enter_code);

    gettimeofday(&tv2, NULL);

    if(tv2.tv_sec - tv1.tv_sec > TLIM){
        boom();
    }

    if( enter_code != pin ){
        boom();
    }

    printf("\nAhora introduce la contraseña\n");
    printf("¿Quieres una pista? (Y/N) ");
    fgets(enter_password, MAXSIZE, stdin);
    fgets(enter_password, MAXSIZE, stdin);

    if(strcmp(enter_password, "Y") == 0 || strcmp(enter_password, "Y\n") == 0){
        printf("De acuerdo: Frase más repetida en matemáticas\n");
    }
    else{
        printf("Okey, vas fuerte eh\n");
    }

    gettimeofday(&tv1, NULL);

    printf("Introduce la contraseña (Tienes 10 segundos): ");
    fgets(enter_password, MAXSIZE, stdin);

    gettimeofday(&tv2, NULL);

    mod_pass();

    if(tv2.tv_sec - tv1.tv_sec > TLIM){
        boom();
    }

    if(strcmp(enter_password, password) != 0){
        boom();
    }
    else{
        defused();
    }

}