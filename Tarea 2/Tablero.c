#include <stdlib.h>
#include <stdio.h>
#include "Cartas.h"
#include "Tablero.h"


typedef struct barquinho {
    int largo;
    char direccion;  
    int fila;
    int columna;
} Barco;

int tamanio;
void*** tablero;


/*
void inicializarTablero(int tamano)
***
Int tamano: requiere del tamaño que tendra el tablero
***
La funcion inicializarTablero crea un tablero de tamaño tamano
***
No retorna nada debido a que es void
*/
 
// Función para inicializar el tablero de juego.
void inicializarTablero(int tamano) {
    int i, j;
    tamanio = tamano;
    tablero = (void ***)malloc(tamano * sizeof(void**));
    for (i = 0; i < tamano; i++) {
        tablero[i] = (void **)malloc(tamano * sizeof(void*));
        for (j = 0; j < tamano; j++) {
            tablero[i][j] = NULL; // Inicializa cada celda a NULL
        }
    }
    return;
}



/*
int verespacio(int fila, int columna, int largo, char direccion)
***
int fila: la fila del barco
int columna: la columna del barco
int largo: el largo del barco
char direccion: si es Horizontal (H) sino vertical (V)
***
La funcion ve si se puede poner un barco en las coordenadas, que este no se salga del tablero y si no queda en otro
***
retorna 1 si se puede ubicar el barco, 0 si no
*/



int cabe(int fila, int columna, int largo, char direccion) {
    int i;
    
    if (direccion == 'H') {
        if (columna + largo > tamanio) return 0; 
        for (i = 0; i < largo; i++) {
            if (tablero[fila][columna + i] != NULL) return 0;
        }
    } else { 
        if (fila + largo > tamanio) return 0; 
        for (i = 0; i < largo; i++) {
            if (tablero[fila + i][columna] != NULL) return 0; 
        }
    // cabe   
    } 
    return 1;
}



/*
void colocarBarco(int tam)
***
Int tam: tamaño de los barcos
***
genera direccion y ubicacion aleatoria para el barco, luego llama a cabe
***
No retorna nada debido a que es void
*/


void colocarBarco(int tam) {
    Barco*barco = (Barco*)malloc(sizeof(Barco));
    barco->largo=tam;
    int direct;
    direct=0;
    while (direct !=1) {
        // Genera una fila y columna aleatoria
        barco->fila = (rand() % (tamanio - 1)) + 1;
        barco->columna = (rand() % (tamanio - 1)) + 1;

        // Genera una dirección aleatoria
        int r = rand() % 2;
        if (r == 0) {
            barco->direccion = 'H';  // Horizontal
        } else {
            barco->direccion = 'V';  // Vertical
        }

        
        if (cabe(barco->fila, barco->columna, barco->largo, barco->direccion)) {
            direct = 1;

            // Coloca el barco en el tablero
            if (barco->direccion == 'H') {
                for (int i = 0; i < barco->largo; i++) {
                    tablero[barco->fila][barco->columna + i] = (void*)1; // Marca el barco
                }
            } else { // 'V'
                for (int i = 0; i < barco->largo; i++) {
                    tablero[barco->fila + i][barco->columna] = (void*)1; // Marca el barco
                }
            }
        }
    }
}

/*
void colocarBarcos(int dificultad)
***
Int dificultad, la dificultad seleccionada por el jugador
***
llama a colocarBarco pasandole los tamaños de los barcos, lo hace 1 vez por barco, por lo que lo llama mas veces cuando mas barcos hay que crear
***
No retorna nada debido a que es void
*/
void colocarBarcos(int dificultad) {
    if (dificultad == 1) { // Fácil
        colocarBarco(2); 
        colocarBarco(2);
        colocarBarco(3); 
        colocarBarco(4); 
        colocarBarco(5); 
    } else if (dificultad == 2) { // Medio
        colocarBarco(2); 
        colocarBarco(2);
        colocarBarco(2);
        colocarBarco(3); 
        colocarBarco(3);
        colocarBarco(4); 
        colocarBarco(5); 
    } else if (dificultad == 3) { // Difícil
        colocarBarco(2); 
        colocarBarco(2);
        colocarBarco(2);
        colocarBarco(3); 
        colocarBarco(3);
        colocarBarco(4); 
        colocarBarco(4);
        colocarBarco(5); 
        colocarBarco(5);
    }
}

/*
void mostrarTablerofinal()
***
no recibe nada
***
muestra el tablero al finalizar el juego, con los barcos sobrevivientes
***
No retorna nada debido a que es void
*/


void mostrarTablerofinal() {
    int i, j;
    for (i = 0; i < tamanio; i++) {
        for (j = 0; j < tamanio; j++) {
            if (tablero[j][i] == (void*)1) {
                printf(" B "); // Imprime "B" si hay un barco
            } else {
                if (i==0 && j==0){
                    printf("__");

                }
                if (j>0 && i==0 && j<10){
                    printf("  %i",j);
                }
                if (j>0 && i==0 && j>9){
                    printf(" %i",j);
                }
            
                if (i>0 && j==0 && i<10){
                    printf(" %i ",i);
                }

                if (j==0 && i>9){
                    printf("%i ",i);
                }

                if(i>0 && j>0 && j<10){
                    printf("__ ");
                }
                if(j>9 && i>0){
                    printf("__ ");
                }
            }
        }
        printf("\n");
    }
}


/*
void mostrarTablero()
***
no recibe nada
***
muestra el tablero, con X para hits, O para los impactos al agua 
***
No retorna nada debido a que es void
*/
void mostrarTablero() {
    int i, j;
    for (i = 0; i < tamanio; i++) {
        for (j = 0; j < tamanio; j++) {
            if (tablero[j][i] == (void*)2) {
                printf(" X "); 
            }else if (tablero[j][i] == (void*)3){
                printf(" O ");
            }else {
                if (i==0 && j==0){
                    printf("__");

                }
                if (j>0 && i==0 && j<10){
                    printf("  %i",j);
                }
                if (j>0 && i==0 && j>9){
                    printf(" %i",j);
                }
            
                if (i>0 && j==0 && i<10){
                    printf(" %i ",i);
                }

                if (j==0 && i>9){
                    printf("%i ",i);
                }

                if(i>0 && j>0 && j<10){
                    printf("__ ");
                }
                if(j>9 && i>0){
                    printf("__ ");
                }
            }
        }
        printf("\n");
    }
}


/*
void ganaste()
***
no recibe nada
***
ve si quedan barcos en el tablero
***
No retorna nada debido a que es void
*/
int ganaste() {
    int i, j;
    int youwin=1;
    for (i = 0; i < tamanio; i++) {
        for (j = 0; j < tamanio; j++) {
            if(tablero[i][j]==(void*)1){
                youwin=0;
                return 0;
            }
        }
    }
    if(youwin==1){
        printf("Wineaste, supreme victory \n");
        return 1;
    }return 0;
}


/*
void liberarTablero()
***
no recibe nada
***
libera la memoria del tablero
***
No retorna nada debido a que es void
*/
void liberarTablero() {
    int i, j;
    for (i = 0; i < tamanio; i++) {      
        for (j = 0; j < tamanio; j++) {
            tablero[i][j] = NULL; 
        }
        free(tablero[i]);
    }
    free(tablero);
}
