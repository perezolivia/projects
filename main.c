#include "matrices.h"

//Esto es para rellenar los circulos
void drawFilledCircle(SDL_Renderer* renderer, int cx, int cy, int radius)
{
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x*x + y*y <= radius*radius) {
                SDL_RenderDrawPoint(renderer, cx + x, cy + y);
            }
        }
    }
}


int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    unsigned char done = 0;
    int **mat,
        filas=0,
        columnas,
        opcion,
        cambio = 0,
        k, i, j;
    char titulo[TAM_TITULO];

    if(argc>=3)
    {
        filas=atoi(argv[1]);
        columnas=atoi(argv[2]);
    }
    mat = IniciarJuego(&filas, &columnas, &opcion);



    SDL_Window* window      = NULL;
    SDL_Renderer* renderer  = NULL;
    SDL_Event e;
    SDL_Rect fillRect;
    fillRect.w = ANCHO;
    fillRect.h = ALTO;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL No se ha podido inicializar! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    //Create window
    window = SDL_CreateWindow("Juego de la vida",
                                                SDL_WINDOWPOS_UNDEFINED,
                                                SDL_WINDOWPOS_UNDEFINED,
                                                1270,
                                                720,
                                                SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("Error en la creacion de la ventana: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // Creamos el lienzo
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("No se ha podido crear el lienzo! SDL Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return ERROR;
    }

    while (!done){
        while (SDL_PollEvent(&e) != 0) {
            // Salida del usuario
            if (e.type == SDL_QUIT) {
                done = 1;
            }
        }


        // Se limpia la pantalla
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        //dibuja las celulas vivas
        for (i = 0; i < filas; i++)
        {
            for (j = 0; j < columnas; j++)
            {
                if (mat[i][j] == 1)
                {
                    fillRect.x = j * ANCHO;
                    fillRect.y = i * ALTO;
                    SDL_SetRenderDrawColor(renderer, 0xF4, 0xC2, 0xC2, 0xFF); //el color del dibujo
                    SDL_RenderFillRect(renderer, &fillRect); // dibuja un rectangulo
                }
            }
        }

        //MostrarMatriz(mat,filas,columnas);

        //logica de las reglas
         cambio = ViveMuere(mat, filas, columnas);

        //Plantilla para pintar circulos si gusta mas
        //drawFilledCircle(renderer, X+e_size_w/2, Y+e_size_h/2, (e_size_w>e_size_h?e_size_h/2:e_size_w/2));

        //Si no hubo cambios tambien termina el juego
        if(!cambio)
        {
            printf("No hubo cambios \nJuego terminado\n");
            done = 1;
        }

        // Actualizacion del "lienzo"
        SDL_RenderPresent(renderer);
        k++;
        //SDL_UpdateWindowSurface(window);

        //Titulo/caption de la ventana
        sprintf(titulo,"Proceso %s",PATRON(opcion)); //es para que muestre el patron selecionado
        SDL_SetWindowTitle(window, titulo);
        SDL_Delay(DELAY);


    }

    //destruyo todos los elementos creados
    //Observar ni mas ni menos que destructores, en la asignatura no inventamos nada!
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    //guardo el ultimo estado
    Guardar_Ultimo_Estado(mat,filas,columnas);
    //libero la memoria
    LiberarMemoria(mat, filas);

    system("pause");
    return 0;
}


