#include "funciones_bernardo.h"

int funcionPrincipal(int argc, char *argv[])
{
    unsigned int i;
    tParametros argumentosRecibidos[TAM_MAX_ARGUMENTOS];
    short estadoArgumento = TODO_OK;
    short valorDelArgumento = TODO_OK;
    int numeroRecibidoEnArg;
    char vNomImg[CANT_IMAGENES][TAM_MAX_PALABRA] = {"No existe","No existe"};

    cantidadParametros ce = 0;

    buscarImagenes(argc-1,argv,vNomImg);

    if(strcmp(vNomImg[0],"No existe") == 0)
    {
        printf("No se encontro el archivo.\n");
        return ERROR_ARCHIVO;
    }

    FILE *img;
    ABRIR_ARCHIVO(img,vNomImg[0],"rb");

    t_bmp structBmp;

    leerMetaData(&structBmp,img);

    t_px **mPixelesOriginal = (t_px**)crearMatriz(structBmp.alto, structBmp.ancho,sizeof(t_px));
    t_px **mPixelesCopia = (t_px**)crearMatriz(structBmp.alto, structBmp.ancho,sizeof(t_px));

    if(!mPixelesCopia || !mPixelesOriginal)
    {
        printf("Sin memoria suficiente.\n");
        return SIN_MEMORIA;
    }

    cargaMatriz(img,mPixelesOriginal,structBmp.alto,structBmp.ancho);

    fclose(img);

    for(i = 1 ; i < argc ; i++)
    {
        copiarMatriz(mPixelesOriginal,mPixelesCopia,&structBmp);

        numeroRecibidoEnArg = numeroEnArgumento(argv[i]);

        if(numeroRecibidoEnArg != NO_TIENE_VALOR_NUMERICO)
        {
            if(!esRangoValido(numeroRecibidoEnArg,100,0))
                valorDelArgumento = VALOR_ARGUMENTO_INVALIDO;
        }

        if(valorDelArgumento == TODO_OK)
            estadoArgumento = ejecutarFuncion(argumentosRecibidos,argv[i],mPixelesCopia,&structBmp,vNomImg,numeroRecibidoEnArg,ce);

        if(estadoArgumento == TODO_OK && valorDelArgumento == TODO_OK)
        {
            strcpy(argumentosRecibidos[ce].parametro,argv[i]);
            argumentosRecibidos[ce].valor = numeroRecibidoEnArg;
            ce++;

        }
        else if((strcmp(argv[i],vNomImg[0]) != 0) && (strcmp(argv[i],vNomImg[1]) != 0))
            mostrarError(estadoArgumento,argv[i]);
    }

    destruirMatriz(mPixelesOriginal,structBmp.alto);
    destruirMatriz(mPixelesCopia,structBmp.alto);

    return TODO_OK;
}
short ejecutarFuncion(tParametros *funcEjecutadas, char *nomFuncion,t_px **mPixelesCopia, t_bmp *structBmp,char vNomImagenes[][TAM_MAX_PALABRA],int valEnArgm,unsigned int cantElem)
{
    short valorDevuelto = TODO_OK;
    bool existe = false;

    unsigned int i;

    for(i = 0; i < cantElem; i++)
    {
        if(strcmp(funcEjecutadas->parametro, nomFuncion) == 0)
            return ARGUMENTO_REPETIDO;

        funcEjecutadas++;
    }

    if(strcmp(nomFuncion,"--negativo") == 0)
    {
        valorDevuelto = funcionNegativo(structBmp,mPixelesCopia,vNomImagenes[0]);
        existe = true;
    }


    if(strcmp(nomFuncion,"--achicar") == 0)
    {
        valorDevuelto = funcionAchicar(structBmp,mPixelesCopia,valEnArgm,vNomImagenes[0]);
        existe = true;
    }

    if(strcmp(nomFuncion,"--recortar") == 0)
    {
        valorDevuelto = funcionRecortar(structBmp,mPixelesCopia,valEnArgm,vNomImagenes[0]);
        existe = true;
    }

    if(strcmp(nomFuncion,"--tonalidad-roja") == 0)
    {
        valorDevuelto = funcionAumentarTonalidadRoja(structBmp,mPixelesCopia,valEnArgm,vNomImagenes[0]);
        existe = true;
    }


    if(strcmp(nomFuncion,"--espejar-vertical") == 0)
    {
        valorDevuelto = funcionEspejarVertical(structBmp,mPixelesCopia,vNomImagenes[0]);
        existe = true;
    }

    if(strcmp(nomFuncion,"--espejar-horizontal") == 0)
    {
        valorDevuelto = funcionEspejarHorizontal(structBmp,mPixelesCopia,vNomImagenes[0]);
        existe = true;
    }


    if(strcmp(nomFuncion,"--rotar-izquierda") == 0)
    {
        valorDevuelto = funcionRotarIzquierda(structBmp,mPixelesCopia,vNomImagenes[0]);
        existe = true;
    }


    if(strcmp(nomFuncion,"--rotar-derecha") == 0)
    {
        valorDevuelto = funcionRotarDerecha(structBmp,mPixelesCopia,vNomImagenes[0]);
        existe = true;
    }

    if(strcmp(nomFuncion,"--concatenar-vertical") == 0)
    {
        if(strcmp(vNomImagenes[1],"No existe") == 0)
            valorDevuelto = FALTA_IMAGEN;
        else
            valorDevuelto = funcionConcatenarVertical(structBmp,mPixelesCopia,vNomImagenes[0],vNomImagenes[1]);

        existe = true;
    }

    if(strcmp(nomFuncion,"--concatenar-horizontal") == 0)
    {
        if(strcmp(vNomImagenes[1],"No existe") == 0)
            valorDevuelto = FALTA_IMAGEN;
        else
            valorDevuelto = funcionConcatenarHorizontal(structBmp,mPixelesCopia,vNomImagenes[0],vNomImagenes[1]);

        existe = true;
    }


    if(strcmp(nomFuncion,"--escala-de-grises") == 0)
    {
        valorDevuelto = funcionEscalaDeGrises(structBmp,mPixelesCopia,vNomImagenes[0]);
        existe = true;
    }


    if(strcmp(nomFuncion,"--tonalidad-azul") == 0)
    {
        valorDevuelto = funcionAumentarTonalidadAzul(structBmp,mPixelesCopia,valEnArgm,vNomImagenes[0]);
        existe = true;
    }

    if(strcmp(nomFuncion,"--tonalidad-verde") == 0)
    {
        valorDevuelto = funcionAumentarTonalidadVerde(structBmp,mPixelesCopia,valEnArgm,vNomImagenes[0]);
        existe = true;
    }


    if(strcmp(nomFuncion,"--aumentar-contraste") == 0)
    {
        valorDevuelto = funcionAumentarContraste(structBmp,mPixelesCopia,valEnArgm,vNomImagenes[0]);
        existe = true;
    }

    if(strcmp(nomFuncion,"--reducir-contraste") == 0)
    {
        valorDevuelto = funcionReducirContraste(structBmp,mPixelesCopia,valEnArgm,vNomImagenes[0]);
        existe = true;
    }

    if(strcmp(nomFuncion,"--comodin") == 0)
    {
        valorDevuelto = funcionComodin(structBmp,mPixelesCopia,valEnArgm,vNomImagenes[0]);
        existe = true;
    }


    if(valorDevuelto != TODO_OK)
        return valorDevuelto;

    if(!existe)
        return ARGUMENTO_INVALIDO;

    return TODO_OK;
}


//FUNCIONES DEL TP
short funcionNegativo(t_bmp *structBmp, t_px **mPixeles,char *nomImagen)
{
    FILE *imgNegativa;

    char nomNuevaImagen[TAM_MAX_PALABRA] = "INEFABLE_negativo_";

    strcat(nomNuevaImagen,nomImagen);

    ABRIR_ARCHIVO(imgNegativa,nomNuevaImagen,"wb");

    escribirMetaData(structBmp,imgNegativa);

    int padding = CALCULAR_PADDING(structBmp->ancho);

    fseek(imgNegativa,structBmp->inidatoimg,SEEK_SET);

    for(int i= 0 ; i < structBmp->alto ; i++)
    {
        for(int j = 0 ; j < structBmp->ancho; j++)
        {
            mPixeles[i][j].pixel[0] = ~mPixeles[i][j].pixel[0];
            mPixeles[i][j].pixel[1] = ~mPixeles[i][j].pixel[1];
            mPixeles[i][j].pixel[2] = ~mPixeles[i][j].pixel[2];

            fwrite(&mPixeles[i][j],sizeof(t_px),1,imgNegativa);
        }

        if(padding > 0 && padding < 4)
            fwrite(&mPixeles[1][1],1,padding,imgNegativa);

    }

    fclose(imgNegativa);

    return TODO_OK;
}

short funcionAchicar(t_bmp *structBmp, t_px **mPixeles, short valor,char *nomImagen)
{
    FILE *imgChica;

    char nomNuevaImagen[TAM_MAX_PALABRA] = "INEFABLE_achicar_";

    strcat(nomNuevaImagen,nomImagen);

    ABRIR_ARCHIVO(imgChica,nomNuevaImagen,"wb");

    escribirMetaData(structBmp,imgChica);

    valor = 100 / valor;

    modificarDimensionesImagen(imgChica,structBmp->alto/valor,structBmp->ancho/valor);

    int padding = CALCULAR_PADDING(((structBmp->ancho)/valor));

    fseek(imgChica,structBmp->inidatoimg,SEEK_SET);

    unsigned int i,j;

    for(i = 0; i < structBmp->alto; i+=valor)
    {
        for(j = 0; j < structBmp->ancho; j+=valor)
            fwrite(&mPixeles[i][j],sizeof(t_px),1,imgChica);

        if(padding > 0 && padding < 4)
            fwrite(&mPixeles[1][1],1,padding,imgChica);
    }


    fclose(imgChica);

    return TODO_OK;
}


short funcionAumentarTonalidadRoja(t_bmp *structBmp, t_px **mPixeles, short valor,char *nomImagen)
{
    FILE *imgRoja;

    char nomNuevaImagen[TAM_MAX_PALABRA] = "INEFABLE_tonalidad-roja_";

    strcat(nomNuevaImagen,nomImagen);

    ABRIR_ARCHIVO(imgRoja,nomNuevaImagen,"wb");

    escribirMetaData(structBmp,imgRoja);

    valor = CALCULAR_PORCENTAJE(255,valor);

    fseek(imgRoja,structBmp->inidatoimg,SEEK_SET);

    unsigned int i,j;

    int padding = CALCULAR_PADDING(structBmp->ancho);

    for(i = 0; i < structBmp->alto; i++)
    {
        for(j = 0; j < structBmp->ancho; j++)
        {
            if(!esRangoValido(valor+mPixeles[i][j].pixel[2],255,0))
                mPixeles[i][j].pixel[2] = 255;
            else
                mPixeles[i][j].pixel[2] += valor;

            fwrite(&mPixeles[i][j],sizeof(t_px),1,imgRoja);
        }

        if(padding > 0 && padding < 4)
            fwrite(&mPixeles[1][1],1,padding,imgRoja);
    }

    fclose(imgRoja);

    return TODO_OK;
}

short funcionEspejarHorizontal(t_bmp *structBmp, t_px **mPixeles,char *nomImagen)
{
    FILE *imgEspejadaHor;

    char nomNuevaImagen[TAM_MAX_PALABRA] = "INEFABLE_espejar-horizontal_";

    strcat(nomNuevaImagen,nomImagen);

    ABRIR_ARCHIVO(imgEspejadaHor,nomNuevaImagen,"wb");

    escribirMetaData(structBmp,imgEspejadaHor);

    int padding = CALCULAR_PADDING(structBmp->ancho);

    fseek(imgEspejadaHor,structBmp->inidatoimg,SEEK_SET);

    unsigned int i,j;

    for(i = 0; i < structBmp->alto; i++)
    {
        for(j = structBmp->ancho; j > 0; j--)
            fwrite(&mPixeles[i][j - 1], sizeof(t_px), 1, imgEspejadaHor);

        if(padding > 0 && padding < 4)
            fwrite(&mPixeles[1][1],1,padding,imgEspejadaHor);
    }


    fclose(imgEspejadaHor);

    return TODO_OK;
}


short funcionRotarIzquierda(t_bmp *structBmp, t_px **mPixeles,char *nomImagen)
{
    FILE *imgRotar;

    char nomNuevaImagen[TAM_MAX_PALABRA] = "INEFABLE_rotar-izquierda_";

    strcat(nomNuevaImagen,nomImagen);

    ABRIR_ARCHIVO(imgRotar,nomNuevaImagen,"wb");

    escribirMetaData(structBmp,imgRotar);

    modificarDimensionesImagen(imgRotar,structBmp->ancho,structBmp->alto);

    int padding = CALCULAR_PADDING(structBmp->alto);

    unsigned int i,j;

    fseek(imgRotar,structBmp->inidatoimg,SEEK_SET);

    for(i = 0; i < structBmp->ancho; i++)
    {
        for(j = 0; j < structBmp->alto; j++)
            fwrite(&mPixeles[structBmp->alto- 1 - j][i],sizeof(t_px),1,imgRotar);

        if(padding > 0 && padding < 4)
            fwrite(&mPixeles[1][1],1,padding,imgRotar);
    }



    fclose(imgRotar);
    return TODO_OK;
}

short funcionRotarDerecha(t_bmp *structBmp, t_px **mPixeles,char *nomImagen)
{
    FILE *imgRotar;

    char nomNuevaImagen[TAM_MAX_PALABRA] = "INEFABLE_rotar-derecha_";

    strcat(nomNuevaImagen,nomImagen);

    ABRIR_ARCHIVO(imgRotar,nomNuevaImagen,"wb");

    escribirMetaData(structBmp,imgRotar);

    modificarDimensionesImagen(imgRotar,structBmp->ancho,structBmp->alto);

    int padding = CALCULAR_PADDING(structBmp->alto);

    unsigned int i,j;

    fseek(imgRotar,structBmp->inidatoimg,SEEK_SET);

    for(i = 0; i < structBmp->ancho; i++)
    {
        for(j = 0; j < structBmp->alto; j++)
            fwrite(&mPixeles[j][structBmp->ancho - 1 -i],sizeof(t_px),1,imgRotar);

        if(padding > 0 && padding < 4)
            fwrite(&mPixeles[1][1],1,padding,imgRotar);
    }

    fclose(imgRotar);
    return TODO_OK;
}

short funcionConcatenarVertical(t_bmp *structBmpImgOrig, t_px **mPixeles,char *nomImagen,char *nomImgConcat)
{
    FILE *imgDos;
    FILE *imgFinal;
    unsigned int anchoMasLargo;
    unsigned int i,j;

    t_bmp structBmpImgDos;

    ABRIR_ARCHIVO(imgDos,nomImgConcat,"rb");
    char nomNuevaImagen[TAM_MAX_PALABRA] = "INEFABLE_concatenar-vertical_";

    strcat(nomNuevaImagen,nomImagen);

    ABRIR_ARCHIVO(imgFinal,nomNuevaImagen,"wb");

    leerMetaData(&structBmpImgDos,imgDos);

    escribirMetaData(structBmpImgOrig,imgFinal);

    if(structBmpImgOrig->ancho > structBmpImgDos.ancho)
        anchoMasLargo = structBmpImgOrig->ancho;
    else
        anchoMasLargo = structBmpImgDos.ancho;

    modificarDimensionesImagen(imgFinal,structBmpImgOrig->alto + structBmpImgDos.alto,anchoMasLargo);

    t_px **mPixelesImgDos = (t_px**)crearMatriz(structBmpImgDos.alto, structBmpImgDos.ancho,sizeof(t_px));

    cargaMatriz(imgDos,mPixelesImgDos,structBmpImgDos.alto,structBmpImgDos.ancho);

    fseek(imgFinal,structBmpImgOrig->inidatoimg,SEEK_SET);

    for(i = 0 ; i < structBmpImgDos.alto + structBmpImgOrig->alto; i++)
    {
        for(j = 0 ; j < anchoMasLargo; j++)
        {
            if(structBmpImgOrig->alto > i)
            {
                if(structBmpImgOrig->ancho < j)
                    fwrite(&mPixeles[1][1],sizeof(t_px),1,imgFinal);
                else
                    fwrite(&mPixeles[i][j],sizeof(t_px),1,imgFinal);

            }
            else
            {
                if(structBmpImgDos.ancho < j)
                    fwrite(&mPixeles[1][1],sizeof(t_px),1,imgFinal);
                else
                    fwrite(&mPixelesImgDos[i - structBmpImgOrig->alto][j],sizeof(t_px),1,imgFinal);
            }
        }
    }

    destruirMatriz(mPixelesImgDos,structBmpImgDos.alto);

    fclose(imgDos);
    fclose(imgFinal);
    return TODO_OK;
}

short funcionConcatenarHorizontal(t_bmp *structBmpImgOrig, t_px **mPixeles,char *nomImagen,char *nomImgConcat)
{
    FILE *imgDos;
    FILE *imgFinal;
    unsigned int altoMasLargo;
    unsigned int i,j;

    t_bmp structBmpImgDos;

    ABRIR_ARCHIVO(imgDos,nomImgConcat,"rb");
    char nomNuevaImagen[TAM_MAX_PALABRA] = "INEFABLE_concatenar-horizontal_";

    strcat(nomNuevaImagen,nomImagen);

    ABRIR_ARCHIVO(imgFinal,nomNuevaImagen,"wb");

    leerMetaData(&structBmpImgDos,imgDos);

    escribirMetaData(structBmpImgOrig,imgFinal);

    if(structBmpImgOrig->alto > structBmpImgDos.alto)
        altoMasLargo = structBmpImgOrig->alto;
    else
        altoMasLargo = structBmpImgDos.alto;

    int padding = CALCULAR_PADDING((structBmpImgDos.ancho + structBmpImgOrig->ancho));

    modificarDimensionesImagen(imgFinal,altoMasLargo,structBmpImgOrig->ancho + structBmpImgDos.ancho);

    t_px **mPixelesImgDos = (t_px**)crearMatriz(structBmpImgDos.alto, structBmpImgDos.ancho,sizeof(t_px));

    cargaMatriz(imgDos,mPixelesImgDos,structBmpImgDos.alto,structBmpImgDos.ancho);

    fseek(imgFinal,structBmpImgOrig->inidatoimg,SEEK_SET);

    for(i = 0 ; i < altoMasLargo; i++)
    {
        for(j = 0 ; j < structBmpImgOrig->ancho + structBmpImgDos.ancho; j++)
        {
            if(structBmpImgOrig->ancho > j)
            {
                if(structBmpImgOrig->alto <= i)
                    fwrite(&mPixeles[1][1],sizeof(t_px),1,imgFinal);
                else
                    fwrite(&mPixeles[i][j],sizeof(t_px),1,imgFinal);

            }
            else
            {
                if(structBmpImgDos.alto <= i)
                    fwrite(&mPixeles[1][1],sizeof(t_px),1,imgFinal);
                else
                    fwrite(&mPixelesImgDos[i][j - structBmpImgOrig->ancho],sizeof(t_px),1,imgFinal);
            }
        }

        if(padding > 0 && padding < 4)
            fwrite(&mPixeles[1][1],1,padding,imgFinal);
    }

    destruirMatriz(mPixelesImgDos,structBmpImgDos.alto);

    fclose(imgDos);
    fclose(imgFinal);
    return TODO_OK;
}

short funcionComodin(t_bmp *structBmp, t_px **mPixeles, short valor,char *nomImagen)
{
    unsigned i, j;
    FILE *imgComodin;

    char nomNuevaImagen[TAM_MAX_PALABRA] = "INEFABLE_comodin_";

    strcat(nomNuevaImagen,nomImagen);

    ABRIR_ARCHIVO(imgComodin,nomNuevaImagen,"wb");

    escribirMetaData(structBmp,imgComodin);

    int padding = CALCULAR_PADDING(structBmp->ancho);

    int radio_cuadrado = CALCULAR_RADIO_CUADRADO(structBmp->alto/4,structBmp->ancho/4,0,0);

    fseek(imgComodin, structBmp->inidatoimg, SEEK_SET);

    for(i = 0; i < structBmp->alto; i++)
    {
        for(j = 0; j < structBmp->ancho; j++)
        {
            if(radio_cuadrado <= CALCULAR_RADIO_CUADRADO(structBmp->alto/2,structBmp->ancho/2,i,j))
            {
                int promedio = ((mPixeles[i][j].pixel[0] + mPixeles[i][j].pixel[2] + mPixeles[i][j].pixel[3]) / 3);
                mPixeles[i][j].pixel[0] = promedio;
                mPixeles[i][j].pixel[1] = promedio;
                mPixeles[i][j].pixel[2] = promedio;

            }

            fwrite(&mPixeles[i][j],sizeof(t_px),1,imgComodin);
        }

        if(padding > 0 && padding < 4)
            fwrite(&mPixeles[1][1],1,padding,imgComodin);
    }

    fclose(imgComodin);

    return TODO_OK;

}


//UTILIZADAS PARA LOS ARGUMENTOS
int numeroEnArgumento(char *argumento)
{

    while(*argumento != '\n' && *argumento != '\0' && *argumento != '=')
        argumento++;


    if(*argumento == '=')
    {
        *argumento = '\0';
        argumento++;
        return atoi(argumento);
    }

    return NO_TIENE_VALOR_NUMERICO;

}
bool esImagen(char *argumento)
{
    char auxPal[5];

    while(*argumento != '\0')
        argumento++;

    auxPal[0] = *(argumento-4);
    auxPal[1] = *(argumento-3);
    auxPal[2] = *(argumento-2);
    auxPal[3] = *(argumento-1);
    auxPal[4] = '\0';

    if(strcmp(auxPal,".bmp") == 0)
        return true;

    return false;
}
void buscarImagenes(int ce, char *arg[], char vNomImg[][TAM_MAX_PALABRA])
{
    unsigned int i=0;
    unsigned int cantImg = 0;

    for(i = 1; i <= ce && cantImg != CANT_IMAGENES; i++)
    {
        if(esImagen(arg[i]))
        {
            strcpy(vNomImg[cantImg],arg[i]);
            cantImg++;
        }

    }
}
void mostrarError(const short codigo,const char *argumento)
{
    switch(codigo)
    {
    case ARGUMENTO_INVALIDO:
        printf("\nNo hay ninguna funcion para el argumento: %s\n",argumento);
        break;

    case ARGUMENTO_REPETIDO:
        printf("\nEl argumento %s esta repetido y ya fue ejecutado\n",argumento);
        break;

    case FALTA_IMAGEN:
        printf("Falta una segunda imagen para el argumento: %s\n",argumento);
        break;
    default:
        printf("Valor numerico del argumento invalido para la funcion: %s\n",argumento);

    }
}



//METADATA DE LA IMAGEN
void escribirMetaData(t_bmp *structBmp, FILE *img)
{

    fwrite(&structBmp->bm,sizeof(char),2,img);
    fwrite(&structBmp->tamanoarch,sizeof(int),1,img);
    fwrite(&structBmp->reservado,sizeof(int),1,img);
    fwrite(&structBmp->inidatoimg,sizeof(int),1,img);
    fwrite(&structBmp->tamanometadatos,sizeof(int),1,img);
    fwrite(&structBmp->ancho,sizeof(int),1,img);
    fwrite(&structBmp->alto,sizeof(int),1,img);
    fwrite(&structBmp->numeroPlanos,sizeof(short int),1,img);
    fwrite(&structBmp->profundidadColor,sizeof(short int),1,img);
    fwrite(&structBmp->tipoCompresion,sizeof(int),1,img);
    fwrite(&structBmp->tamanoEstructura,sizeof(int),1,img);
    fwrite(&structBmp->pxmh,sizeof(int),1,img);
    fwrite(&structBmp->pxmv,sizeof(int),1,img);
    fwrite(&structBmp->coloresUsados,sizeof(int),1,img);
    fwrite(&structBmp->coloresImportantes,sizeof(int),1,img);
}

void leerMetaData(t_bmp *structBmp,FILE *img)
{

    rewind(img);

    fread(&structBmp->bm,sizeof(char),2,img);//BM
    fread(&structBmp->tamanoarch,sizeof(int),1,img);//Arch tamanio
    fread(&structBmp->reservado,sizeof(int),1,img);//reservado
    fread(&structBmp->inidatoimg,sizeof(int),1,img);//inicio dato img
    fread(&structBmp->tamanometadatos,sizeof(int),1,img);//tamanio metadato
    fread(&structBmp->ancho,sizeof(int),1,img);//alto
    fread(&structBmp->alto,sizeof(int),1,img);//ancho
    fread(&structBmp->numeroPlanos,sizeof(short int),1,img);//numero planos
    fread(&structBmp->profundidadColor,sizeof(short int),1,img);//profundidad color
    fread(&structBmp->tipoCompresion,sizeof(int),1,img); //tipo comprension
    fread(&structBmp->tamanoEstructura,sizeof(int),1,img); //tamaño estructtura
    fread(&structBmp->pxmh,sizeof(int),1,img);//px m horizontal
    fread(&structBmp->pxmv,sizeof(int),1,img);
    fread(&structBmp->coloresUsados,sizeof(int),1,img);
    fread(&structBmp->coloresImportantes,sizeof(int),1,img);
}

void modificarDimensionesImagen(FILE *img, int nuevoAlto, int nuevoAncho)
{
    fseek(img,POS_ALTO,SEEK_SET);
    fwrite(&nuevoAlto,sizeof(int),1,img);
    fseek(img,POS_ANCHO,SEEK_SET);
    fwrite(&nuevoAncho,sizeof(int),1,img);
}



//MANEJO DE MATRICES
void **crearMatriz(const size_t filas, const size_t columnas, size_t tamDato)
{
    void **mat = (void **)malloc(sizeof(void*) * filas);

    if(!mat)
        return NULL;

    void **ultimo = mat + filas - 1; //No hace falta multiplicar por sizeof porque es un puntero y ya sabe el tamaño

    for(void **i = mat ; i <= ultimo ; i++)
    {
        *i = (void*) malloc(tamDato * columnas);
        if(!*i)
        {
            for(void **j = mat ; j <=  i - 1; j++)
                free(*j);

            free(mat);

            return NULL;
        }
    }

    return mat;
}

void cargaMatriz(FILE *img, t_px **matriz, unsigned int alto, unsigned int ancho)
{
    int posIniImagen;

    fseek(img,10,SEEK_SET);
    fread(&posIniImagen,sizeof(int),1,img);

    int padding = CALCULAR_PADDING(ancho);

    fseek(img,posIniImagen,SEEK_SET);

    for(int i = 0 ; i < alto; i++)
    {
        for(int j = 0 ; j < ancho; j++)
            fread(&matriz[i][j], sizeof(t_px), 1, img);

        if(padding >  0 && padding < 4)
            fread(&matriz[1][1],1, padding, img);
    }


}

void destruirMatriz(t_px **matriz,int filas)
{
    int i;

    for(i = 0; i < filas; i++)
    {
        free(*(matriz+i));
        *(matriz+i) = NULL;
    }


    free(matriz);
    matriz = NULL;
}

void copiarMatriz(t_px **mRead, t_px **mWrite,t_bmp *structBmp)
{
    unsigned int i,j;

    for(i = 0 ; i < structBmp->alto ; i++)
        for(j = 0; j < structBmp->ancho; j++)
            mWrite[i][j] = mRead[i][j];
}



//FUNCIONES EXTRAS

int ajustarContraste(int n,int max,int min,float porc) //n=color ,max=maximo,min=minimo, porc=porcentaje (a disminuir o sumar)
{
    if(porc > min)
    {
        if(n+(n*porc) > max)
            return max;
        else
            return n+(n*porc);
    }
    else
    {
        if(n+(n*porc) < min)
            return min;
        else
            return n+(n*porc);
    }

}


bool esRangoValido(int valor, int mayor, int menor)
{
    if(valor > mayor || valor < menor)
        return false;

    return true;
}
