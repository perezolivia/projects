#include "funciones_perez.h"


short funcionEspejarVertical (t_bmp *structBmp, t_px **mPixeles,char *nomImagen)
{
    unsigned int i, j;

    FILE *imgEspejadaVert;

    char nomNuevaImagen[TAM_MAX_PALABRA] = "INEFABLE_espejar-vertical_";

    strcat(nomNuevaImagen,nomImagen);

    ABRIR_ARCHIVO(imgEspejadaVert,nomNuevaImagen,"wb");

    escribirMetaData(structBmp,imgEspejadaVert);

    int padding = CALCULAR_PADDING(structBmp->ancho);

    fseek(imgEspejadaVert, structBmp->inidatoimg, SEEK_SET);

    for(i = structBmp->alto; i > 0; i--)
    {
        for(j = 0; j < structBmp->ancho; j++)
            fwrite(&mPixeles[i-1][j], sizeof(t_px), 1, imgEspejadaVert);

        if(padding >  0 && padding < 4)
            fwrite(&mPixeles[1][1],1, padding, imgEspejadaVert);
    }


    fclose(imgEspejadaVert);


    return TODO_OK;
}

short funcionRecortar(t_bmp *structBmp, t_px **mPixeles, short valor,char *nomImagen)
{
    FILE *imgRecortada;

    char nomNuevaImagen[TAM_MAX_PALABRA] = "INEFABLE_recortar_";

    strcat(nomNuevaImagen,nomImagen);

    ABRIR_ARCHIVO(imgRecortada,nomNuevaImagen,"wb");

    escribirMetaData(structBmp,imgRecortada);

    valor = 100 / valor;

    unsigned int nuevoAlto = structBmp->alto / valor;
    unsigned int nuevoAncho = structBmp->ancho / valor;

    modificarDimensionesImagen(imgRecortada,nuevoAlto, nuevoAncho);

    int padding = CALCULAR_PADDING(nuevoAncho);

    unsigned int i,j;

    fseek(imgRecortada,structBmp->inidatoimg,SEEK_SET);

    for(i = 0; i < nuevoAlto; i++)
    {
        for(j = 0; j < nuevoAncho; j++)
            fwrite(&mPixeles[i][j],sizeof(t_px),1,imgRecortada);

        if(padding >  0 && padding < 4)
            fwrite(&mPixeles[1][1],1, padding, imgRecortada);
    }


    fclose(imgRecortada);

    return TODO_OK;
}

short funcionEscalaDeGrises(t_bmp *structBmp, t_px **mPixeles,char *nomImagen)
{
    FILE *imgGrises;

    unsigned int i, j;

    unsigned int promedio;

    char nomNuevaImagen[TAM_MAX_PALABRA] = "INEFABLE_escala-de-grises_";

    strcat(nomNuevaImagen,nomImagen);

    ABRIR_ARCHIVO(imgGrises,nomNuevaImagen,"wb");

    escribirMetaData(structBmp,imgGrises);

    int padding = CALCULAR_PADDING(structBmp->ancho);

    fseek(imgGrises,structBmp->inidatoimg,SEEK_SET);

    for(i = 0; i < structBmp->alto; i++)
    {
        for(j = 0; j < structBmp->ancho; j++)
        {
            promedio = ((mPixeles[i][j].pixel[0] + mPixeles[i][j].pixel[2] + mPixeles[i][j].pixel[3]) / 3);
            mPixeles[i][j].pixel[0] = promedio;
            mPixeles[i][j].pixel[1] = promedio;
            mPixeles[i][j].pixel[2] = promedio;

            fwrite(&mPixeles[i][j],sizeof(t_px), 1, imgGrises);
        }

        if(padding >  0 && padding < 4)
            fwrite(&mPixeles[1][1],1, padding, imgGrises);
    }

    fclose(imgGrises);

    return TODO_OK;
}

short funcionAumentarTonalidadAzul (t_bmp *structBmp, t_px **mPixeles, short valor,char *nomImagen)
{
    FILE *imgAzul;

    unsigned int i, j;

    char nomNuevaImagen[TAM_MAX_PALABRA] = "INEFABLE_tonalidad-azul_";

    strcat(nomNuevaImagen,nomImagen);

    ABRIR_ARCHIVO(imgAzul,nomNuevaImagen,"wb");

    escribirMetaData(structBmp,imgAzul);

    int padding = CALCULAR_PADDING(structBmp->ancho);

    valor = CALCULAR_PORCENTAJE(255, valor);

    fseek(imgAzul, structBmp->inidatoimg, SEEK_SET);


    for(i = 0; i < structBmp->alto; i++)
    {
        for(j = 0; j < structBmp->ancho; j++)
        {
            if(!esRangoValido(valor+mPixeles[i][j].pixel[0],255,0))
                mPixeles[i][j].pixel[0] = 255;
            else
                mPixeles[i][j].pixel[0] += valor;

            fwrite(&mPixeles[i][j], sizeof(t_px), 1, imgAzul);
        }

        if(padding >  0 && padding < 4)
            fwrite(&mPixeles[1][1],1, padding, imgAzul);
    }

    fclose(imgAzul);

    return TODO_OK;
}

short funcionAumentarTonalidadVerde (t_bmp *structBmp, t_px **mPixeles, short valor,char *nomImagen)
{
    FILE *imgVerde;

    char nomNuevaImagen[TAM_MAX_PALABRA] = "INEFABLE_tonalidad-verde_";

    strcat(nomNuevaImagen,nomImagen);

    unsigned int i, j;

    ABRIR_ARCHIVO (imgVerde,nomNuevaImagen,"wb");

    escribirMetaData(structBmp,imgVerde);

    valor = CALCULAR_PORCENTAJE(255, valor);

    int padding = CALCULAR_PADDING(structBmp->ancho);

    fseek(imgVerde, structBmp->inidatoimg, SEEK_SET);

    for(i = 0; i < structBmp->alto; i++)
    {
        for(j = 0; j < structBmp->ancho; j++)
        {
            if(!esRangoValido(valor+mPixeles[i][j].pixel[1],255,0))
                mPixeles[i][j].pixel[1] = 255;
            else
                mPixeles[i][j].pixel[1] += valor;

            fwrite(&mPixeles[i][j], sizeof(t_px), 1, imgVerde);
        }

        if(padding >  0 && padding < 4)
            fwrite(&mPixeles[1][1],1, padding, imgVerde);
    }

    fclose(imgVerde);

    return TODO_OK;
}

short funcionAumentarContraste(t_bmp *structBmp, t_px **mPixeles, short valor,char *nomImagen)
{
    unsigned i, j;

    FILE * imgMasContraste;

    char nomNuevaImagen[TAM_MAX_PALABRA] = "INEFABLE_aumentar-contraste_";

    strcat(nomNuevaImagen,nomImagen);

    ABRIR_ARCHIVO(imgMasContraste,nomNuevaImagen,"wb");

    escribirMetaData(structBmp, imgMasContraste);

    float valorPorc = CALCULAR_PORCENTAJE(1, valor);//Porque nuestra formula para validar el rango utiliza un rango entre 0 y 1

    int padding = CALCULAR_PADDING(structBmp->ancho);

    fseek(imgMasContraste, structBmp->inidatoimg, SEEK_SET);

    for(i = 0; i < structBmp->alto; i++)
    {
        for(j = 0; j < structBmp->ancho; j++)
        {
            float promPixel = (float)(mPixeles[i][j].pixel[0] + mPixeles[i][j].pixel[1] + mPixeles[i][j].pixel[2])/3;

            if(promPixel < 127.5)
            {
                mPixeles[i][j].pixel[0] = ajustarContraste(mPixeles[i][j].pixel[0],127,0,-valorPorc);
                mPixeles[i][j].pixel[1] = ajustarContraste(mPixeles[i][j].pixel[1],127,0,-valorPorc);
                mPixeles[i][j].pixel[2] = ajustarContraste(mPixeles[i][j].pixel[2],127,0,-valorPorc);
            }
            else
            {
                mPixeles[i][j].pixel[0] = ajustarContraste(mPixeles[i][j].pixel[0],255,0,valorPorc);
                mPixeles[i][j].pixel[1] = ajustarContraste(mPixeles[i][j].pixel[1],255,0,valorPorc);
                mPixeles[i][j].pixel[2] = ajustarContraste(mPixeles[i][j].pixel[2],255,0,valorPorc);
            }

            fwrite(&mPixeles[i][j], sizeof(t_px), 1, imgMasContraste);
        }

        if(padding >  0 && padding < 4)
            fwrite(&mPixeles[1][1],1, padding, imgMasContraste);
    }

    fclose(imgMasContraste);

    return TODO_OK;
}


short funcionReducirContraste(t_bmp *structBmp, t_px **mPixeles, short valor,char *nomImagen)
{
    unsigned i, j;
    FILE *imgContrasteMenos;

    char nomNuevaImagen[TAM_MAX_PALABRA] = "INEFABLE_reducir-contraste_";

    strcat(nomNuevaImagen,nomImagen);

    ABRIR_ARCHIVO(imgContrasteMenos,nomNuevaImagen,"wb");

    escribirMetaData(structBmp,imgContrasteMenos);

    int padding = CALCULAR_PADDING(structBmp->ancho);

    fseek(imgContrasteMenos, structBmp->inidatoimg, SEEK_SET);

    for(i = 0; i < structBmp->alto; i++)
    {
        for(j = 0; j < structBmp->ancho; j++)
        {
            float promPixel = (float)(mPixeles[i][j].pixel[0] + mPixeles[i][j].pixel[1] + mPixeles[i][j].pixel[2])/3;

            if(promPixel > 127.5)
            {
                mPixeles[i][j].pixel[0] = ajustarContraste(mPixeles[i][j].pixel[0],255,127,(float)-(valor)/100);
                mPixeles[i][j].pixel[1] = ajustarContraste(mPixeles[i][j].pixel[1],255,127,(float)-(valor)/100);
                mPixeles[i][j].pixel[2] = ajustarContraste(mPixeles[i][j].pixel[2],255,127,(float)-(valor)/100);
            }
            else
            {
                mPixeles[i][j].pixel[0] = ajustarContraste(mPixeles[i][j].pixel[0],127,0,(float)valor/100);
                mPixeles[i][j].pixel[1] = ajustarContraste(mPixeles[i][j].pixel[1],127,0,(float)valor/100);
                mPixeles[i][j].pixel[2] = ajustarContraste(mPixeles[i][j].pixel[2],127,0,(float)valor/100);
            }

            fwrite(&mPixeles[i][j], sizeof(t_px), 1, imgContrasteMenos);
        }

        if(padding >  0 && padding < 4)
            fwrite(&mPixeles[1][1],1, padding, imgContrasteMenos);
    }

    fclose(imgContrasteMenos);

    return TODO_OK;
}
