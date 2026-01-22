#ifndef MATRICES_H_INCLUDED
#define MATRICES_H_INCLUDED

//--------------------Librerías Incluídas---------------------------
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //para la espera
#include <string.h>
#include <locale.h> // para los printf

//PARTE B
//--------------------------SDL--------------------------------------

#ifdef __MINGW32__
    #define SDL_MAIN_HANDLED
    #include <SDL_main.h>
#endif

#include <SDL.h>


//--------------------Constantes Generales---------------------------
//Interfaz y visualización
#define TAM_TITULO 50
#define ANCHO 25
#define ALTO 25
#define DELAY 100

//Estados del programa

#define ERROR 0
#define TODO_OK 1
#define PATRON_INVALIDO -1

//Restricciones de tamaño
#define MINFC 6
#define MAX_VECINOS 2

//Identificación de patrones
#define PULSADOR 1
#define SAPO 2
#define CANION 3
#define PLANEADOR 4
#define ULTIMO_ESTADO 5
#define MAX_PATRONES 5


//Estados de las celulas
#define MUERTA 0
#define VIVA 1
#define MUERE 2
#define NACE 3

//Tamaño mínimo para cada patrón
#define MIN_FILAS_PULSADOR 17
#define MIN_COLUMNAS_PULSADOR 17

#define MIN_FILAS_SAPO 6
#define MIN_COLUMNAS_SAPO 6

#define MIN_FILAS_CANION 15
#define MIN_COLUMNAS_CANION 37

#define MIN_FILAS_PLANEADOR 10
#define MIN_COLUMNAS_PLANEADOR 6

//Reglas del juego
#define VECINOS_NACIMIENTO 3
#define MAX_VECINOS_SOBREVIVE 3
#define MIN_VECINOS_SOBREVIVE 2

//Nombres de patrones
#define PATRON(X) ((X)==1 ? "Pulsador" : \
                  (X)==2 ? "Sapo" : \
                  (X)==3 ? "Canion de planeadores" : \
                  (X)==4 ? "Planeadores" : \
                  (X)==5 ? "Ultimo Estado" :"")

//Nombres Archivos
#define ARCH_SAPO "Sapo.txt"
#define ARCH_PLANEADOR "Planeador.txt"
#define ARCH_PLANEADORES "Canon_de_planeadores.txt"
#define ARCH_PULSAR "Pulsar.txt"
#define ARCH_ESTADO_SIMULACION "Estado_simulacion.txt"

//Tam para el buffer
#define TAM_BUFFER 1000
/*REGLAS
Nace
Si una célula muerta tiene exactamente 3 células vecinas vivas "nace" (es decir,
al turno siguiente estará viva).
Muere
una célula viva puede morir por uno de 2 casos:
o Sobrepoblación: si tiene más de tres vecinos alrededor.
o Aislamiento: si tiene solo un vecino alrededor o ninguno.
Vive
una célula se mantiene viva si tiene 2 o 3 vecinos a su alrededor.
*/

//REGLAS NUESTRAS
/*
0 = muerta
1= viva
2= viva que pasa a muerta
3= muerta que pasa a viva
*/

//PARTE 1
//PARTE A

//--------------------Declaración de Funciones---------------------------
//GESTIÓN DE MATRIZ
int **IniciarJuego(int *Filas, int *Columnas, int *Opcion);
int **CrearMatriz(size_t filas, size_t columnas);
void LiberarMemoria(int** mat, size_t Filas);
int ValidarTamMatriz(int *Filas, int *Columnas);

//MENU Y PATRONES
int menu(int filas, int columnas);
int MostrarPatronesDisponibles(size_t Filas, size_t Columnas, int *pPatrones);
int RegistrarPatronValido(size_t Filas, size_t Columnas, int TipoPatron, int *ListaPatrones, int indice, const char *NombrePatron);
int ValidarOpcion(int CantOpciones);
int ValidarPatron(size_t filas, size_t columnas, int num);
void InicializarMatriz(int **mat, unsigned opcion, size_t filas, size_t columnas);
void LimpiarMatriz(int **mat, size_t Filas, size_t Columnas);
void AplicarPatron(int **mat, unsigned int Opcion);
int FC_Ultimo_Estado(int *Filas,int *Columnas);



//PATRONES ESPECÍFICOS
int Pulsar(int **mat);
int Sapo(int **mat);
int CanionDePlaneadores(int **mat);
int Planeador(int **mat);
int Ultimo_estado(int **mat);
//para contar las filas del ultimo estado
int contarcolum(char *buffer);

//TROZAR
void trozar(char *buffer,int **mat,size_t f,size_t c);
//Crea el archivo con el ultimo estado
int Guardar_Ultimo_Estado(int **mat,size_t filas,size_t columnas);

//REGLAS DEL JUEGO
int ViveMuere(int **mat, size_t filas, size_t columnas);
int CantidadVecinos(int **mat, unsigned posf, unsigned posc, size_t filas,size_t columnas);
void Generacion(int **mat, size_t filas, size_t columnas);

//VISUALIZACIÓN
void MostrarMatriz(int **mat, size_t filas, size_t columnas);



#endif // MATRICES_H_INCLUDED

