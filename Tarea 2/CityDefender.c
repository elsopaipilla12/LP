#include <stdlib.h>
#include <stdio.h>
#include "Cartas.h"
#include "Tablero.h"
#include <time.h>


/*
***
int argc: Numero de argumentos en la linea de comandos.
char const *argv[]: Un puntero a un arreglo de caracteres constantes.
***
La funcion main enlaza todo lo necesario para poder realizar un uso correcto del programa, y ejecutar el juego de forma correcta
***
Retorna 0 en caso de que el programa se ejecute como lo esperado.
***
*/

int main(int argc, char const *argv[]) {
    srand(time(NULL)); // Inicializa la semilla aleatoria

    int dificultad,max,seg;
    seg=1;
    while (1) {
        printf("Selecciona la Dificultad:\n");
        printf("1. Facil -> 11 X 11 , 5 Barcos\n");
        printf("2. Medio -> 17 X 17 , 7 Barcos\n");
        printf("3. Dificil -> 21 X 21 , 9 Barcos\n");
        printf("4. Ahora no quiero \n");
        printf("Ingrese un numero: ");
        scanf("%d", &dificultad);
        
        if (dificultad == 1) {
            printf("Turno 1\n");
            tamanio = 12;
            max=30;
            printf("\n");
            break;
        } else if (dificultad == 2) {
            printf("Turno 1\n");
            tamanio = 18;
            max=25;
            printf("\n");
            break;
        } else if (dificultad == 3) {
            printf("Turno 1\n");
            tamanio = 22;
            max=15;
            printf("\n");
            break;
        } else if (dificultad == 4) {
            printf("No defendiste la costa, pero hey almenos no perdiste \n");
            seg=0;
            break;
        } else {
            printf("Por tu chistesito perdimos la salida al mar, GRACIAS \n");
            seg=0;
            break;
        }
    }
    if(seg==1){
        inicializarTablero(tamanio);
        colocarBarcos(dificultad);
        mostrarTablero(); // Muestra el tablero con los barcos colocados
        mostrarTablerofinal();
        printf("\n");
        inicializarMazo();
        int turno;
        turno=2;
        while (1) {
            printf("Cartas disponibles:\n");
            mostrarMazo();
            usarCarta();
            mostrarTablero();

            printf("Turno %d\n", turno);
            turno++;

            if (turno <= max ) {
                if(ganaste()==1){
                    mostrarTablerofinal();
                    break;
                }else{
                    continue;
                }
             
            } else {
                mostrarTablerofinal(); 
                break; 
            }   
        }
    }
    liberarMazo();
        //mostrarTablerofinal();
    return 0;
}

