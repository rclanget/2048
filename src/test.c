// Compilation: gcc myfile.c -w -lSDL2 -lSDL2-image
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string.h>
#include "inc.h"

int init(SDL_Window **window, SDL_Surface **screenSurface, SDL_Renderer **renderer)
{
  int status;

  status = 1;
  if ((SDL_Init(SDL_INIT_VIDEO) < 0) || TTF_Init() == -1)
  {
    printf("SDL Error: %s\n", SDL_GetError());
    status = 0;
  }
  else
  {
    // Create window
    *window = SDL_CreateWindow("SDL Tuto", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (*window == NULL)
    {
      printf("SDL Error: %s\n", SDL_GetError());
      status = 0;
    }
    else
    {
      // Create renderer
      *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
      if (*renderer == NULL)
      {
        printf("SDL Error: %s\n", SDL_GetError());
        status = 0;
      }
      else
      {
        // Initialize renderer color
        SDL_SetRenderDrawColor(*renderer, 0xFF, 0xFF, 0xFF, 0xFF);

        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
        {
            printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
            status = 0;
        }
      }
    }
  }
  return (status);
}

int loadmedia(void)
{
  int         status;

  status = 1;
  return (status);
}

int main(int argc, char** argv)
{
  SDL_Window    *window = NULL;
  SDL_Surface   *screenSurface = NULL;
  SDL_Surface   *texte = NULL;
  SDL_Texture   *message = NULL;
  SDL_Event     e;
  int           quit;
  SDL_Renderer  *renderer = NULL;
  TTF_Font      *police = NULL;
  SDL_Color     couleurNoire = {0, 0, 0};
  SDL_Rect      position;

  SDL_Rect textrect;
  int w = 0;
  int h = 0;

  if (init(&window, &screenSurface, &renderer) && (police = TTF_OpenFont("police/elegant.ttf", 70)))
  {
    if (loadmedia())
    {
      //Main loop flag
      quit = 0;
      //While application is running
      while(!quit)
      {
        //Handle events on queue
        while(SDL_PollEvent(&e) != 0)
        {
          //User requests quit
          if(e.type == SDL_QUIT)
          {
              printf("Click on \"X\"\n");
              quit = 1;
          }
        }
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 189, 189, 189, 1);
        SDL_RenderClear(renderer);

        // Render red filled quad
        SDL_Rect fillRect = {10, 10, 150, 150};
        SDL_SetRenderDrawColor(renderer, 140, 140, 140, 1);
        SDL_RenderFillRect(renderer, &fillRect);
        // Render red filled quad
        SDL_Rect fillRect2 = {170, 10, 150, 150};
        SDL_SetRenderDrawColor(renderer, 140, 140, 140, 1);
        SDL_RenderFillRect(renderer, &fillRect2);

        // Render red filled quad
        SDL_Rect fillRect3 = {330, 10, 150, 150};
        SDL_SetRenderDrawColor(renderer, 140, 140, 140, 1);
        SDL_RenderFillRect(renderer, &fillRect3);

        // Render red filled quad
        SDL_Rect fillRect4 = {490, 10, 150, 150};        
        SDL_SetRenderDrawColor(renderer, 140, 140, 140, 1);
        SDL_RenderFillRect(renderer, &fillRect4);

       /* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
        texte = TTF_RenderText_Blended(police, "2048", couleurNoire);
        message = SDL_CreateTextureFromSurface(renderer, texte);
        SDL_QueryTexture(message, NULL, NULL, &w, &h);
        textrect.x = 0; textrect.y = 55; textrect.w = w; textrect.h = h;
        SDL_RenderCopy(renderer, message, NULL, &textrect);

        SDL_RenderPresent(renderer);
      }
    }
  }
  // Destroy window
  SDL_DestroyWindow(window);
  //Close TTF Font 
  TTF_CloseFont(police);
  //Quit TTF
  TTF_Quit();
  // Quit SDL
  SDL_Quit();
  return (0);
}