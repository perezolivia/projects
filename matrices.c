#include "matrices.h"
//PARTE 1
//PARTE  A
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int **IniciarJuego(int *Filas, int *Columnas,  int *Opcion)
{
    int **Mat;
    if(ValidarTamMatriz(Filas, Columnas)==1)
        return NULL;
    *Opcion = menu(*Filas, *Columnas); //Para que se elija el modo de inicializacion
    Mat = CrearMatriz(*Filas, *Columnas);//se le asigna memoria para la matriz
    if(!Mat)
    {
        printf("\nNo se pudo reservar memoria para la matriz");
        return ERROR;
    }
    InicializarMatriz(Mat, *Opcion, *Filas, *Columnas);
    return Mat;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int menu(int Filas, int Columnas)
{
    unsigned int Opcion = 0;
    int CantPatrones = 0;
    int Patrones[MAX_PATRONES]; //guarda los patrones válidos
    int *pPatrones = Patrones;
    printf("Para la matriz %d x %d\n", Filas, Columnas);

    printf("Opciones de patrones disponibles:\n");
    CantPatrones = MostrarPatronesDisponibles(Filas, Columnas, pPatrones);

    Opcion = ValidarOpcion(CantPatrones);

    return *(Patrones + Opcion - 1);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MostrarPatronesDisponibles(size_t Filas, size_t Columnas, int *ListaPatrones)
{
    int CantPatrones = 0;

    CantPatrones += RegistrarPatronValido(Filas, Columnas, PULSADOR, ListaPatrones, CantPatrones, "Pulsador");
    CantPatrones += RegistrarPatronValido(Filas, Columnas, SAPO, ListaPatrones, CantPatrones, "Sapo");
    CantPatrones += RegistrarPatronValido(Filas, Columnas, CANION, ListaPatrones, CantPatrones, "Cañón");
    CantPatrones += RegistrarPatronValido(Filas, Columnas, PLANEADOR, ListaPatrones, CantPatrones, "Planeador");
    CantPatrones += RegistrarPatronValido(Filas,Columnas,ULTIMO_ESTADO,ListaPatrones,CantPatrones,"Ultimo estado"); //por el de iniciar desde el ultimo registro
    return CantPatrones;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RegistrarPatronValido(size_t Filas, size_t Columnas, int TipoPatron, int *ListaPatrones, int indice, const char *NombrePatron)
{
    if(ValidarPatron(Filas, Columnas, TipoPatron))
    {
        printf("%d) %s\n", indice + 1, NombrePatron);
        *(ListaPatrones + indice) = TipoPatron;
        return TODO_OK;
    }
    return ERROR;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ValidarOpcion(int CantOpciones)
{
    int Opcion;
    do{
            printf("Seleccione una opción: ");
            scanf("%d", &Opcion);

            if(Opcion < 1 || Opcion > CantOpciones)
                printf("La opción seleccionada es inválida. Intente nuevamente.\n");

    }while(Opcion < 1 || Opcion > CantOpciones);
    return Opcion;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Para validar los rangos
int ValidarPatron(size_t Filas, size_t Columnas, int Num)
{
    int MinFilas = 0;
    int MinColumnas = 0;
    switch(Num)
    {
    case PULSADOR: //requiere al menos 16 filas y 13 columnas
        MinFilas = MIN_FILAS_PULSADOR;
        MinColumnas = MIN_COLUMNAS_PULSADOR;
        break;

    case SAPO:  //requiere al menos 6 filas y 6 columnas
        MinFilas = MIN_FILAS_SAPO;
        MinColumnas = MIN_COLUMNAS_SAPO;
        break;

    case CANION: //requiere al menos 15 filas y 10 columnas
        MinFilas = MIN_FILAS_CANION;
        MinColumnas = MIN_COLUMNAS_CANION;
        break;

    case PLANEADOR: //requiere al menos 10 filas y 6 columnas
        MinFilas = MIN_FILAS_PLANEADOR;
        MinColumnas = MIN_COLUMNAS_PLANEADOR;
        break;
    case ULTIMO_ESTADO:
        FC_Ultimo_Estado(&MinFilas,&MinColumnas);
        break;
    default:
        return PATRON_INVALIDO;
    }
    if(Filas >= MinFilas && Columnas >= MinColumnas)
        return TODO_OK;

    return ERROR;
}
int FC_Ultimo_Estado(int *Filas,int *Columnas)
{
    FILE *pf;
    char buffer[TAM_BUFFER],*ptem;
    pf=fopen(ARCH_ESTADO_SIMULACION,"rt");
    if(!pf)
    {
        return ERROR;
    }
    fgets(buffer,TAM_BUFFER,pf);
    ptem=strrchr(buffer,'-');
    if(!ptem)
    {
        fclose(pf);
        *Filas=-1;//para decir que son invalidas
        *Columnas=-1;
        return ERROR;
    }
    sscanf(ptem+1,"%d",Columnas);
    *ptem='\0';
    sscanf(buffer,"%d",Filas);
    fclose(pf);
    return TODO_OK;

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ValidarTamMatriz(int *Filas, int *Columnas)
{
    int F, C;
    if(*Filas==0)
    {
        do
        {
            printf("Elija el tamaño de la matriz para empezar el juego\n");
            printf("La matriz debe ser por lo menos de 6x6\n");
            printf("Tamaño filas:");
            scanf("%d", &F);
            printf("Tamaño columnas:");
            scanf("%d", &C);

            if(F < MINFC || C < MINFC)
            {
                system("cls");
                printf("No se puede iniciar el juego con una matriz de %dx%d\n\n", F, C);
            }
        }
        while(F < MINFC || C < MINFC);
        *Filas = F;
        *Columnas = C;
    }
    else
    {
        if(*Filas<MINFC || *Columnas < MINFC)
            {
                system("cls");
                printf("No se puede iniciar el juego con una matriz de %dx%d\n\n", *Filas, *Columnas);
                return 1;
            }
    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InicializarMatriz(int **mat, unsigned Opcion, size_t Filas, size_t Columnas)
{
    LimpiarMatriz(mat, Filas, Columnas);
    AplicarPatron(mat, Opcion);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LimpiarMatriz(int **mat, size_t Filas, size_t Columnas)
{
    size_t F, C;
    for(F = 0; F < Filas; F++)
        for(C = 0 ; C < Columnas; C++)
            mat[F][C] = 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AplicarPatron(int **mat, unsigned Opcion)
{
    switch (Opcion)
    {
    case PULSADOR:
        Pulsar(mat);
        break;
    case SAPO:
        Sapo(mat);
        break;
    case CANION:
        CanionDePlaneadores(mat);
        break;
    case PLANEADOR:
        Planeador(mat);
        break;
    case ULTIMO_ESTADO:
        Ultimo_estado(mat);
        break;
    default:
        printf("Opción de patrón inválida. No se aplicó ningún patrón.\n");
        break;
    }
}
//PATRONES
//PULSAR
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Pulsar(int **mat)
{
     FILE *pf;
    char buffer[TAM_BUFFER];
    int f=0;

    pf=fopen(ARCH_PULSAR,"rt");
    if(!pf)
    {
        return ERROR;
    }

    while(fgets(buffer,TAM_BUFFER,pf))
    {
        trozar(buffer,mat,f,MIN_COLUMNAS_PULSADOR);
        f++;
    }
    fclose(pf);
    return TODO_OK;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SAPO
int Sapo(int **mat)
{
      FILE *pf;
    char buffer[TAM_BUFFER];
    int f=0;

    pf=fopen(ARCH_SAPO,"rt");
    if(!pf)
    {
        return ERROR;
    }

    while(fgets(buffer,TAM_BUFFER,pf))
    {
        trozar(buffer,mat,f,MIN_COLUMNAS_SAPO);
        f++;
    }
    fclose(pf);
    return TODO_OK;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CAÑON DE PLANEADORES
int CanionDePlaneadores(int **mat)
{
        FILE *pf;
    char buffer[TAM_BUFFER];
    int f=0;

    pf=fopen(ARCH_PLANEADORES,"rt");
    if(!pf)
    {
        return ERROR;
    }

    while(fgets(buffer,TAM_BUFFER,pf))
    {
        trozar(buffer,mat,f,MIN_COLUMNAS_CANION);
        f++;
    }
    fclose(pf);
    return TODO_OK;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//PLANEADOR
int Planeador(int **mat)
{
    FILE *pf;
    char buffer[TAM_BUFFER];
    int f=0;

    pf=fopen(ARCH_PLANEADOR,"rt");
    if(!pf)
    {
        return ERROR;
    }

    while(fgets(buffer,TAM_BUFFER,pf))
    {
        trozar(buffer,mat,f,MIN_COLUMNAS_PLANEADOR);
        f++;
    }
    fclose(pf);
    return TODO_OK;
}
//ULTIMO ESTADO
int Ultimo_estado(int **mat)
 {
       FILE *pf;
    char buffer[TAM_BUFFER];
    int f=0,c=0;

    pf=fopen(ARCH_ESTADO_SIMULACION,"rt");
    if(!pf)
    {
        return ERROR;
    }

    fgets(buffer, TAM_BUFFER, pf); // <- esta línea ignora la cabecera
    // Ahora leemos la primera línea real
    if (fgets(buffer, TAM_BUFFER, pf))
    {
        c = contarcolum(buffer);
        trozar(buffer, mat, f, c);
        f++;
    }

    // Leer el resto de las líneas
    while(fgets(buffer, TAM_BUFFER, pf))
    {
        trozar(buffer, mat, f, c);
        f++;
    }

    fclose(pf);
    return TODO_OK;
 }

 int contarcolum(char *buffer)
 {
     int cont=0;
     char *aux=buffer;
     while(*aux!='\n' && *aux!='\0')
     {
         cont++;
         aux++;
     }
     return cont;
 }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Trozar
void trozar(char *buffer,int **mat,size_t f,size_t c)
{
    int i;
    for(i=0;i<c;i++)
    {
        if(*buffer=='O')
        {
            mat[f][i]=1;
        }
        buffer++;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//REGLAS
//En esta funcion solo vemos que celula pasa de muerta a viva y viceversa
int ViveMuere(int **mat, size_t filas, size_t columnas)
{
    int  i, j , vecinos = 0, Cambios = 0;
    for(i = 0 ; i < filas ; i++)
    {
        for(j =0 ; j < columnas ; j++)
        {
            vecinos = CantidadVecinos(mat, i, j, filas, columnas);

            if(mat[i][j] == MUERTA && vecinos == VECINOS_NACIMIENTO) // nace una celula
            {
                mat[i][j] = NACE;
                Cambios++;
            }

            else if(mat[i][j] == VIVA && (vecinos < MIN_VECINOS_SOBREVIVE || vecinos > MAX_VECINOS_SOBREVIVE)) //muere una celula
            {
                mat[i][j] = MUERE;
                Cambios++;
            }
        }
    }
    Generacion(mat, filas, columnas);
    return Cambios;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//En esta funcion cambaiamos la celula de muerta a viva o de viva a muerta
void Generacion(int **mat,size_t filas,size_t columnas)
{
    size_t i, j;
    for(i = 0; i < filas; i++)
    {
        for(j = 0; j < columnas; j++)
        {
            if(mat[i][j] == MUERE)
                mat[i][j] = MUERTA;

            else if(mat[i][j] == NACE)
                mat[i][j] = VIVA;
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CantidadVecinos(int **mat,unsigned posf,unsigned posc,size_t filas,size_t columnas)
{
    int vecinos = 0, i, j, ColumnaVecina, FilaVecina, Estado;
    for(i = -1; i < MAX_VECINOS ; i++)
    {
        for(j = -1;  j < MAX_VECINOS ; j++)
        {
            ColumnaVecina = posc + j;
            FilaVecina = posf + i;

             //para verificar que no nos pasemos de los limites
             if(!(i == 0 && j == 0) && FilaVecina < filas && ColumnaVecina < columnas)
            {
                Estado = mat[FilaVecina][ColumnaVecina];
                if(Estado == VIVA || Estado == MUERE)
                    vecinos++;
            }
        }
    }
    return vecinos;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MostrarMatriz(int **mat, size_t filas, size_t columnas)
{
    int i, j;
    int ancho = columnas * MINFC + 1;

    for(i = 0; i < ancho; i++)
        printf("-");

    printf("\n");

    for(i = 0 ; i < filas ; i++)
    {
        printf("|");
        for(j = 0; j < columnas ; j++)
            printf(" %4d|", mat[i][j]);

        printf("\n");

        for(j = 0; j < ancho; j++)
            printf("-");
        printf("\n");
    }
    printf("\n");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//PARTE 2
int **CrearMatriz(size_t filas, size_t columnas)
{
    size_t i;
    int **mat = (int**)malloc(filas*sizeof(int*));//sizeof de *int porque la matriz es doble puntero y las filas apuntan a un array de int

    //SI NO SE PUEDE ASIGNAR MEMORIA SE RETORNA NULL(0)
    if(mat == NULL)
        return NULL;

    //asinamos memoria para las columnas
    for(i = 0; i < filas;i++)
    {
        *(mat + i ) = (int*)malloc(columnas * sizeof(int)); //asigno a cada fila las columnas
        //sizeof de int porque las columnas son un array de int (secuencia de datos enteros)

        //SI NO SE PUEDE ASIGNAR MEMORIA SE LIBERA TODO
        if(*(mat + i) == NULL)
        {
            LiberarMemoria(mat, i); //libera solo hasta la fila fallida
            return NULL;
        }
    }
    return mat;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Guardar_Ultimo_Estado(int **mat,size_t filas,size_t columnas)
{
    FILE *pf;
    int i,j;

    pf=fopen(ARCH_ESTADO_SIMULACION,"wt");
    if(!pf)
    {
        return ERROR;
    }
    fprintf(pf,"%d-%d",(int)filas,(int)columnas);
    fprintf(pf,"\n");

    for(i=0;i<filas;i++)
    {
        for(j=0;j<columnas;j++)
        {
            if(mat[i][j]==1)
            {
                fprintf(pf,"%c",'O');
            }
            else
            {
                fprintf(pf,"%c",'.');
            }
        }
        fprintf(pf,"\n");
    }
    fclose(pf);
    return TODO_OK;

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LiberarMemoria(int** mat, size_t Filas)
{
    size_t i;
    for(i = 0; i < Filas; i++)
        free(*(mat + i)); //liberamos cada fila

    free(mat); //liberamos todo el arreglo de punteros
}
