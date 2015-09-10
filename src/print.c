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

SDL_Renderer *define_color(SDL_Renderer *renderer, int value)
{
  if (value < 2)
    SDL_SetRenderDrawColor(renderer, COLOREMPTY, 1);
  else if (value == 2)
    SDL_SetRenderDrawColor(renderer, COLOR2, 1);
  else if (value == 4)
    SDL_SetRenderDrawColor(renderer, COLOR4, 1);
  else if (value == 8)
    SDL_SetRenderDrawColor(renderer, COLOR8, 1);
  else if (value == 16)
    SDL_SetRenderDrawColor(renderer, COLOR16, 1);
  else if (value == 32)
    SDL_SetRenderDrawColor(renderer, COLOR32, 1);
  else if (value == 64)
    SDL_SetRenderDrawColor(renderer, COLOR64, 1);
  else if (value == 128)
    SDL_SetRenderDrawColor(renderer, COLOR128, 1);
  else if (value == 256)
    SDL_SetRenderDrawColor(renderer, COLOR256, 1);
  else if (value == 512)
    SDL_SetRenderDrawColor(renderer, COLOR512, 1);
  else if (value == 1024)
    SDL_SetRenderDrawColor(renderer, COLOR1024, 1);
  else
    SDL_SetRenderDrawColor(renderer, COLOR2048, 1);
  return (renderer);
}

SDL_Renderer *print_case(SDL_Renderer *renderer, int value, int xcase, int ycase, TTF_Font *police)
{
  int x;
  int y;
  SDL_Surface   *texte = NULL;
  SDL_Texture   *message = NULL;
  SDL_Rect textrect;
  int w = 0;
  int h = 0;
  SDL_Color     couleurNoire = {0, 0, 0};

  int textx = 20 + (15 * (4 - ft_nbrlen(value))) + (160 * xcase);

  renderer = define_color(renderer, value);
  x = 10 + (160 * xcase);
  y = 10 + (160 * ycase);
  SDL_Rect fillRect = {x, y, 150, 150};
  SDL_RenderFillRect(renderer, &fillRect);

   /* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
  texte = TTF_RenderText_Blended(police, (value < 2 ? "" : ft_itoa(value)), couleurNoire);
  message = SDL_CreateTextureFromSurface(renderer, texte);
  SDL_QueryTexture(message, NULL, NULL, &w, &h);
  textrect.x = textx; textrect.y = 55 + (160 * ycase); textrect.w = w; textrect.h = h;
  SDL_RenderCopy(renderer, message, NULL, &textrect);
  return (renderer);

}

void 	print_map(t_map *map, TTF_Font *police, SDL_Renderer *renderer)
{


    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 1);
    SDL_RenderClear(renderer);

	while (map)
	{
		renderer = print_case(renderer, map->value, map->x, map->y, police);
		map = map->next;
	}
    SDL_RenderPresent(renderer);
}