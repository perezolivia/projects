#ifndef FUNCIONES_CANDADOCABANAS_H_INCLUDED
#define FUNCIONES_CANDADOCABANAS_H_INCLUDED
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define TODO_OK 0
#define ARCHIVO_NO_ENCONTRADO -5
#define NO_SE_PUEDE_CREAR_ARCHIVO 20
#define IMAGEN_NO_ENCONTRADA 30
#define TAM_MAX_ARGUMENTOS 20
#define SIN_MEMORIA -10
#define TAM_MAX_PALABRA 100
#define SIN_PORCENTAJE -101
#define ARGUMENTO_INVALIDO -10
#define ARGUMENTO_REPETIDO -11
#define TIENE_VALOR_NUMERICO 'S'
#define NO_TIENE_VALOR_NUMERICO 'N'
#define POS_ANCHO 18
#define POS_ALTO 22
#define NO_ENCONTRADO -40
#define ERROR_ARCHIVO -41
#define VALOR_ARGUMENTO_INVALIDO -42

#define CANT_IMAGENES 2
#define FALTA_IMAGEN -3

#define ABRIR_ARCHIVO(X,Y,Z) {(X) = fopen((Y),(Z));\
                            if((X) == NULL)\
                            {printf("Error al abrir la imagen. \n");return NO_SE_PUEDE_CREAR_ARCHIVO;}}


#define CALCULAR_PORCENTAJE(MAX,NUM) (((float)(MAX)*(NUM)) / 100)
#define CALCULAR_PADDING(NUM) (4-((NUM*3)%4))
#define CALCULAR_RADIO_CUADRADO(xCentro,yCentro,xActual,yActual) (((yCentro-yActual)*(yCentro-yActual) + (xCentro-xActual)*(xCentro-xActual)))

typedef struct
{
    unsigned char bm[2]; //(2 Bytes) BM (Tipo de archivo)
    unsigned int tamanoarch; //(4 Bytes) Tamano del archivo en bytes
    unsigned int reservado; //(4 Bytes) Reservado
    unsigned int inidatoimg; //(4 Bytes) offset, distancia en bytes entre la img y los pixeles
    unsigned int tamanometadatos;//(4 Bytes) Tamano de Metadatos (tamano de esta estructura = 40)
    unsigned int ancho; //(4 Bytes) Ancho (numero de pixeles horizontales)
    unsigned int alto; //(4 Bytes) Alto (numero de pixeles verticales)
    unsigned short int numeroPlanos; //(2 Bytes) Numero de planos de color
    unsigned short int profundidadColor;//(2 Bytes) Profundidad de color (debe ser 24 para nuestro caso)
    unsigned int tipoCompresion;//(4 Bytes) Tipo de compresion (Vale 0, ya que el bmp es descomprimido)
    unsigned int tamanoEstructura;//(4 Bytes) Tamano de la estructura Imagen (Paleta)
    unsigned int pxmh; //(4 Bytes) Pixeles por metro horizontal
    unsigned int pxmv; //(4 Bytes) Pixeles por metro vertical
    unsigned int coloresUsados;//(4 Bytes) Cantidad de colores usados
    unsigned int coloresImportantes; //(4 Bytes) Cantidad de colores importantes
} t_bmp;

typedef struct
{
    unsigned char pixel[3];//0->Azul , 1->Verde , 2->Rojo
} t_px;

typedef struct
{
    char parametro[TAM_MAX_PALABRA];
    short valor;

} tParametros;


typedef unsigned int cantidadParametros;

int funcionPrincipal(int argc, char* []);

//FUNCIONES EXTRAS
void buscarImagenes(int ce, char *arg[],char vNomImg[][TAM_MAX_PALABRA]);
bool esRangoValido(int valor, int mayor, int menor);

//FUNCIONES PARA LOS ARGUMENTOS
int esArgumentoValido(const char *argumentoRecibido,const tParametros *parametros);
int numeroEnArgumento(char *argumento);
bool esArgumentoRepetido(const char *argumento,const tParametros *parametro,cantidadParametros cantElem);
bool comparaArgumentos(const char *argumento);
char separaValorArgumento(char *argumento);
int valorNumericoArgumento(char *argumento);
void mostrarError(const short codigo, const char *argumento);
bool esImagen(char *argumento);



void cargaMatriz(FILE *img,t_px **matriz, unsigned int alto, unsigned int ancho);
void **crearMatriz(const size_t filas,const size_t columnas,const size_t tamDato);
short ejecutarFuncion(tParametros *funcEjecutadas, char *nomFuncion,t_px **mPixelesCopia, t_bmp *structBmp,char vNomImagenes[][TAM_MAX_PALABRA],int valEnArgm,unsigned int cantElem);
int cargaDatos(FILE *arch,FILE *arch2);
void leerMetaData(t_bmp *structBmp, FILE *img);
void escribirMetaData(t_bmp *structBmp, FILE *img);
void modificarDimensionesImagen(FILE *img, int nuevoAlto, int nuevoAncho);
void destruirMatriz(t_px **matriz, int filas);
void mostrarVector(tParametros *parametro, cantidadParametros ce);
void copiarMatriz(t_px **mRead, t_px **mWrite,t_bmp *structBmp);

short funcionAchicar(t_bmp *structBmp, t_px **mPixeles, short valorAchicar,char *nomImagen);
short funcionNegativo(t_bmp *structBmp, t_px **mPixeles,char *nomImagen);
short funcionRecortar(t_bmp *structBmp, t_px **mPixeles, short valor,char *nomImagen);
short funcionAumentarTonalidadRoja(t_bmp *structBmp, t_px **mPixeles, short valor,char *nomImagen);
short funcionRotarIzquierda(t_bmp *structBmp, t_px **mPixeles,char *nomImagen);
short funcionRotarDerecha(t_bmp *structBmp, t_px **mPixeles,char *nomImagen);
short funcionConcatenarVertical(t_bmp *structBmpImgOrig, t_px **mPixeles,char *nomImagen,char *nomImgConcat);
short funcionConcatenarHorizontal(t_bmp *structBmpImgOrig, t_px **mPixeles,char *nomImagen,char *nomImgConcat);
short funcionEspejarHorizontal (t_bmp *structBmp, t_px **mPixeles,char *nomImagen);
short funcionComodin(t_bmp *structBmp, t_px **mPixeles, short valor,char *nomImagen);
short funcionEspejarVertical(t_bmp *structBmp, t_px **mPixeles,char *nomImagen);
short funcionEscalaDeGrises(t_bmp *structBmp, t_px **mPixeles,char *nomImagen);
short funcionAumentarTonalidadAzul (t_bmp *structBmp, t_px **mPixeles, short valor,char *nomImagen);
short funcionAumentarContraste(t_bmp *structBmp, t_px **mPixeles, short valor,char *nomImagen);
short funcionAumentarTonalidadVerde(t_bmp *structBmp,t_px **mPixeles, short valor,char *nomImagen);
short funcionReducirContraste(t_bmp *structBmp, t_px **mPixeles, short valor,char *nomImagen);

int ajustarContraste (int n,int max,int min,float porc);


#endif // FUNCIONES_CANDADOCABANAS_H_INCLUDED
