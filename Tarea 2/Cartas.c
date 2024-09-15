#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct Mano
{
    void ** carta;
    int disponibles;

} Mano;

Mano *mano;
extern void ***tablero;
extern int tamanio;
void **posc;
//mano->disponibles = valor entero de la carta
//int poscar;
//char texto_1;
//char texto_2;
//char texto_3;
// printf("Dirección de mano->carta[%d]: %p, Dirección de j: %p\n", i, mano->carta[i], *j);
int lapotente = 0;




/*
void inicializarMazo()
***
no recibe nada
***
crea 5 cartas simples
***
No retorna nada debido a que es void
*/

void inicializarMazo(){
    int i;
    mano = (Mano*)malloc(sizeof(Mano)); 
    mano->carta = malloc(5 * sizeof(void*));
    for (i = 0; i < 5; i++) {
        mano->carta[i] = malloc(sizeof(int));
        *(int *)mano->carta[i] = 1;   
        posc = &mano->carta[i];  
    }
}


/*
void mostrarMazo()
***
no recibe nada
***
muestra las cartas que uno tiene
***
No retorna nada debido a que es void
*/
void mostrarMazo(){
    int i;
    for (i = 0; i < 5; i++) {
        int valor_carta = *(int *)(mano->carta[i]);

       
        if (valor_carta == 1) {
            printf("| Simple |");
        } else if (valor_carta == 2) {
            printf("| Grande |");
        } else if (valor_carta == 3) {
            printf("| Lineal |");
        } else if (valor_carta == 4) {
            printf("| Radar |");
        } else if (valor_carta == 5) {
            printf("| 500 KG |");
        } else {
            printf("| - |");
        }
    }
    printf("\n");
}


/*
void * disparoSimple(int x, int y)()
***
int x coordenada x ingresada por el jugador
int y coordenada y ingresada por el jugador
***
disparo que afecta una celda 1x1 y se actualiza el valor del puntero
***
No retorna nada debido a que es void
*/



void * disparoSimple(int x, int y){ //tomara un cuadrado de coordenadas x,y
    if (tablero[x][y] == (void *)1) {
        tablero[x][y] = (void *)2; // HIT
    } else {
        tablero[x][y] = (void *)3; // Agua
    }
 
    int random = rand() % 100;
    if (random < 65) {
        *(int *)(mano->carta[mano->disponibles]) = 1; // simple 
    } else if (random < 85) {
        *(int *)(mano->carta[mano->disponibles]) = 2; // grande        
    } else if (random < 90) {
        *(int *)(mano->carta[mano->disponibles]) = 3; // lineal      
    } else {
        *(int *)(mano->carta[mano->disponibles]) = 4; // radar  
    }
    return NULL;
}



/*
void * disparoGrande (int x, int y)()
***
int x coordenada x ingresada por el jugador
int y coordenada y ingresada por el jugador
***
disparo que afecta una cantidad de celdas 3x3 y se actualiza el valor del puntero
***
No retorna nada debido a que es void
*/

void * disparoGrande(int x, int y){//tomara un cuadrado de 3x3 centro x,y
    int x2,y2;
    for ( x2 = -1; x2 <= 1; x2++) {
        for ( y2 = -1; y2 <= 1; y2++) {
            int nx = x + x2, ny = y + y2;
            if (nx >= 0 && nx < tamanio && ny >= 0 && ny < tamanio) {
                if (tablero[nx][ny] == (void *)1) {
                    tablero[nx][ny] = (void *)2; // hit
                } else {
                    tablero[nx][ny] = (void *)3; // Agua
                }
            }
        }
    }
    // Retornar cartas según porcentajes
    int random = rand() % 100;
    if (random < 80) {
        *(int *)(mano->carta[mano->disponibles]) = 1;// simple 
    } else if (random < 83) {
        *(int *)(mano->carta[mano->disponibles]) = 2;// grande  
    } else if (random < 93) {
        *(int *)(mano->carta[mano->disponibles]) = 3;// lineal  
    } else if (random < 98) {
        *(int *)(mano->carta[mano->disponibles]) = 4;// radar  
    } else if (!lapotente) { 
        *(int *)(mano->carta[mano->disponibles]) = 5; // 500kg
        lapotente = 1;
    } else {
        *(int *)(mano->carta[mano->disponibles]) = 1; 
    }
    return NULL;
}



/*
void * disparoLineal(int x, int y)()
***
int x coordenada x ingresada por el jugador
int y coordenada y ingresada por el jugador
***
disparo que afecta una cantidad de celdas 1x5 segun la direccion que el jugador elija y se actualiza el valor del puntero
***
No retorna nada debido a que es void
*/

void * disparoLineal(int x, int y){ //tomara una linea de 1x5 segun la direccion
    int direct, i;
    printf("Elija dirección: \n");
    printf("1 para horizontal\n");
    printf("2 para vertical\n");
    scanf("%d", &direct);

    if (direct == 1) {
        // Horizontal
        for (i = -2; i <= 2; i++) {
            int nx = x + i;
            if (nx >= 0 && nx < tamanio) {
                if (tablero[nx][y] == (void*)1) {
                    tablero[nx][y] = (void*)2;
                    //printf("HIT \n");
                } else {
                    tablero[nx][y] = (void*)3;
                    //printf("MISS \n");
                }
            }
        }
    } else if (direct == 2) {
        // Vertical
        for (i = -2; i <= 2; i++) {
            int ny = y + i;
            if (ny >= 0 && ny < tamanio) {
                if (tablero[x][ny] == (void*)1) {
                    tablero[x][ny] = (void*)2;
                } else {
                    tablero[x][ny] = (void*)3;
                }
            }
        }
    } else {
        printf("Elija una opción válida\n");
        disparoLineal(x, y);
    }

    int random = rand() % 100;
    if (random < 85) { // 85% 
        *(int *)(mano->carta[mano->disponibles]) = 1;// simple 
    } else if (random < 90) { // 5% 
        *(int *)(mano->carta[mano->disponibles]) = 2;// grande  
    } else if (random < 92) { // 2% 
        *(int *)(mano->carta[mano->disponibles]) = 3;// lineal  
    } else if (random < 98) { // 6% 
        *(int *)(mano->carta[mano->disponibles]) = 4;// radar  
    } else if (!lapotente) { //2%
        *(int *)(mano->carta[mano->disponibles]) = 5; // 500kg
        lapotente = 1;
    } else {
        *(int *)(mano->carta[mano->disponibles]) = 1; 
    }
    return NULL;
}


/*
void * disparoRadar(int x, int y)()
***
int x coordenada x ingresada por el jugador
int y coordenada y ingresada por el jugador
***
disparo que afecta una cantidad de celdas 5x5 pero no golpea, solo revela si hay barcos ahi y se actualiza el valor del puntero
***
No retorna nada debido a que es void
*/
void * disparoRadar(int x, int y){ //tomara un cuadrado de 5x5 centro x,y
    int x2,y2;
    int sihay=0;
    for ( x2 = -2; x2 <= 2; x2++) {
        for ( y2 = -2; y2 <= 2; y2++) {
            int nx = x + x2, ny = y + y2;
            if (nx >= 0 && nx < tamanio && ny >= 0 && ny < tamanio) {
                if (tablero[nx][ny] == (void *)1) {
                    printf("Hay barcos en el radio del radar. \n");
                    sihay=1;
                    break;
                } 
            }
        }
    
        if(sihay==1){
            break;
        }
    }
    if(sihay==0){
        printf("No hay barcos en el radio del radar. \n");
    }
    int random = rand() % 100;
    if (random < 75) {
        *(int *)(mano->carta[mano->disponibles]) = 1;// simple 
    } else if (random < 90) {
        *(int *)(mano->carta[mano->disponibles]) = 2;// grande  
    } else if (random < 95) {
        *(int *)(mano->carta[mano->disponibles]) = 3;// lineal  
     } else if (!lapotente) { 
        *(int *)(mano->carta[mano->disponibles]) = 5; // 500kg
        lapotente = 1;
    } else {
        *(int *)(mano->carta[mano->disponibles]) = 1; 
    }
    return NULL;
}


/*
void * disparo500KG(int x, int y)()
***
int x coordenada x ingresada por el jugador
int y coordenada y ingresada por el jugador
***
disparo que afecta una cantidad de celdas 11x11 y se actualiza el valor del puntero
***
No retorna nada debido a que es void
*/


void * disparo500KG(int x, int y){ //tomara un cuadrado de 11x11 centro x,y

    int x2,y2;
    for ( x2 = -5; x2 <= 5; x2++) {
        for ( y2 = -5; y2 <= 5; y2++) {
            int nx = x + x2, ny = y + y2;
            if (nx >= 0 && nx < tamanio && ny >= 0 && ny < tamanio) {
                if (tablero[nx][ny] == (void *)1) {
                    tablero[nx][ny] = (void *)2;
                } else {
                    tablero[nx][ny] = (void *)3;
                }
            }
        }
    }
    *(int *)(mano->carta[mano->disponibles]) = 6;
    return NULL;
}



/*
void lacarta(int opc)
***
int opc carta elegida por el jugarod
***
le pide las coordenadas x,y al jugador y luego llama al disparo correspondiente
***
No retorna nada debido a que es void
*/
void lacarta(int opc){
     int x, y;

    printf("Seleccione coordenadas: \n");
    printf("X: ");
    scanf("%d", &x);
    printf("Y: ");
    scanf("%d", &y);

   
    mano->disponibles = opc - 1;  

    if (*(int *)(mano->carta[mano->disponibles]) == 1) {
        disparoSimple(x, y);  
    } else if (*(int *)(mano->carta[mano->disponibles]) == 2) {
        disparoGrande(x, y); 
    } else if (*(int *)(mano->carta[mano->disponibles]) == 3) {
        disparoLineal(x, y); 
    } else if (*(int *)(mano->carta[mano->disponibles]) == 4) {
        disparoRadar(x, y);   
    } else if (*(int *)(mano->carta[mano->disponibles]) == 5) {
        disparo500KG(x, y);   
    } else {
        printf("Elija una opción válida\n");
        scanf("%d", &opc);
        lacarta(opc);
    }
}



/*
void * usarCarta()
***
no hay parametros
***
le pide al jugador que elija una carta, luego llama a lacarta
***
No retorna nada debido a que es void
*/
void usarCarta(){
    int opc;
    printf("\nSeleccione la carta (1-5): ");
    scanf("%d", &opc);
    
    
    if (opc < 1 || opc > 5) {
        printf("Elija una opcin valida \n");
        usarCarta();  
    } else {
        lacarta(opc);  
    }
}



/*
void liberarMazo() 
***
no hay parametros
***
libera la memora del mazo
***
No retorna nada debido a que es void
*/
void liberarMazo() {
    if (mano != NULL) {
        for (int i = 0; i < 5; i++) {
            if (mano->carta[i] != NULL) {
                free(mano->carta[i]);  
                mano->carta[i] = NULL; 
            }
        }

        free(mano->carta); 
        mano->carta = NULL; 

        free(mano);
        mano = NULL;
    }
}