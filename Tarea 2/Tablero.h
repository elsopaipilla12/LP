#ifndef H_TABLERO
#define H_TABLERO

extern void *** tablero;
extern int tamanio;

void inicializarTablero(int tamano);
int cabe(int fila, int columna, int largo, char direccion);
void colocarBarco(int largo);
void colocarBarcos(int dificultad);
void mostrarTablero();
void mostrarTablerofinal();
void liberarTablero();
int ganaste();

#endif
