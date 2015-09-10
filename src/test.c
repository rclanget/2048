// Compilation: gcc myfile.c -w -lSDL2 -lSDL2-image -lSDL2-ttf

#include "inc.h"


int main(int argc, char** argv)
{

  TTF_Font    *police = NULL;
  SDL_Window    *window = NULL;
  SDL_Surface   *screenSurface = NULL;
  SDL_Renderer  *renderer = NULL;
  SDL_Event   e;
  int       quit;

  if (init(&window, &screenSurface, &renderer) && (police = TTF_OpenFont("police/elegant.ttf", 70)))
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
        print_map(map, police, renderer);
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