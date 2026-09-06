#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define MAX_CUERPO 100

typedef struct {
    int x;
    int y;
} Segmento;

int main(int argc, char* argv[]) {
    srand(time(NULL));
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;
    
    SDL_Window* ventana = SDL_CreateWindow("Vortex Snake - Puntos: 0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer* pintor = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED);
    
    int tamano = 20;
    
    Segmento cuerpo[MAX_CUERPO];
    int largo_cuerpo = 3;
    
    cuerpo[0].x = 300; cuerpo[0].y = 240;
    cuerpo[1].x = 280; cuerpo[1].y = 240;
    cuerpo[2].x = 260; cuerpo[2].y = 240;
    
    int dir_x = tamano; 
    int dir_y = 0;

    int manzana_x = (rand() % (640 / tamano)) * tamano;
    int manzana_y = (rand() % (480 / tamano)) * tamano;

    int puntos = 0;
    bool juego_corriendo = true;
    bool game_over = false;
    SDL_Event evento;
    Uint32 ultimo_tiempo = SDL_GetTicks();
    
    // TRUCO: Bandera para bloquear multiples giros en un mismo cuadro de tiempo
    bool ya_giro_este_turno = false;

    while (juego_corriendo) {
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) juego_corriendo = false;
            else if (evento.type == SDL_KEYDOWN) {
                switch (evento.key.keysym.sym) {
                    case SDLK_ESCAPE: juego_corriendo = false; break;
                    
                    // Solo permitimos el giro si NO hemos girado en este ciclo de 120ms
                    case SDLK_UP:    if (dir_y == 0 && !game_over && !ya_giro_este_turno) { dir_x = 0; dir_y = -tamano; ya_giro_este_turno = true; } break;
                    case SDLK_DOWN:  if (dir_y == 0 && !game_over && !ya_giro_este_turno) { dir_x = 0; dir_y = tamano; ya_giro_este_turno = true; } break;
                    case SDLK_LEFT:  if (dir_x == 0 && !game_over && !ya_giro_este_turno) { dir_x = -tamano; dir_y = 0; ya_giro_este_turno = true; } break;
                    case SDLK_RIGHT: if (dir_x == 0 && !game_over && !ya_giro_este_turno) { dir_x = tamano; dir_y = 0; ya_giro_este_turno = true; } break;
                    
                    case SDLK_SPACE:
                        if (game_over) {
                            largo_cuerpo = 3;
                            cuerpo[0].x = 300; cuerpo[0].y = 240;
                            cuerpo[1].x = 280; cuerpo[1].y = 240;
                            cuerpo[2].x = 260; cuerpo[2].y = 240;
                            dir_x = tamano; dir_y = 0;
                            puntos = 0;
                            game_over = false;
                            ya_giro_este_turno = false;
                            SDL_SetWindowTitle(ventana, "Vortex Snake - Puntos: 0");
                        }
                        break;
                }
            }
        }

        if (!game_over && (SDL_GetTicks() - ultimo_tiempo > 120)) {
            ultimo_tiempo = SDL_GetTicks();
            
            // Permitir un nuevo giro en el siguiente paso de la serpiente
            ya_giro_este_turno = false;

            for (int i = largo_cuerpo - 1; i > 0; i--) {
                cuerpo[i] = cuerpo[i - 1];
            }

            cuerpo[0].x += dir_x;
            cuerpo[0].y += dir_y;

            if (cuerpo[0].x < 0 || cuerpo[0].x >= 640 || cuerpo[0].y < 0 || cuerpo[0].y >= 480) {
                game_over = true;
            }

            for (int i = 1; i < largo_cuerpo; i++) {
                if (cuerpo[0].x == cuerpo[i].x && cuerpo[0].y == cuerpo[i].y) {
                    game_over = true;
                }
            }

            if (cuerpo[0].x == manzana_x && cuerpo[0].y == manzana_y) {
                puntos += 10;
                if (largo_cuerpo < MAX_CUERPO) {
                    largo_cuerpo++;
                }
                
                char titulo[50];
                sprintf(titulo, "Vortex Snake - Puntos: %d", puntos);
                SDL_SetWindowTitle(ventana, titulo);

                manzana_x = (rand() % (640 / tamano)) * tamano;
                manzana_y = (rand() % (480 / tamano)) * tamano;
            }
        }

        if (game_over) {
            SDL_SetRenderDrawColor(pintor, 150, 20, 20, 255);
            SDL_RenderClear(pintor);
            char titulo_go[100];
            sprintf(titulo_go, "GAME OVER - Final: %d - [ESPACIO] reiniciar", puntos);
            SDL_SetWindowTitle(ventana, titulo_go);
        } else {
            SDL_SetRenderDrawColor(pintor, 15, 15, 30, 255);
            SDL_RenderClear(pintor);

            SDL_Rect rect_manzana = { manzana_x, manzana_y, tamano, tamano };
            SDL_SetRenderDrawColor(pintor, 240, 50, 50, 255);
            SDL_RenderFillRect(pintor, &rect_manzana);

            for (int i = 0; i < largo_cuerpo; i++) {
                SDL_Rect rect_seg = { cuerpo[i].x, cuerpo[i].y, tamano - 2, tamano - 2 };
                if (i == 0) {
                    SDL_SetRenderDrawColor(pintor, 100, 255, 100, 255);
                } else {
                    SDL_SetRenderDrawColor(pintor, 34, 175, 34, 255);
                }
                SDL_RenderFillRect(pintor, &rect_seg);
            }
        }

        SDL_RenderPresent(pintor);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(pintor);
    SDL_DestroyWindow(ventana);
    SDL_Quit();
    return 0;
}
