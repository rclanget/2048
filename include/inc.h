#ifndef INC_H
# define INC_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 		650
#define HEIGHT 		650

// Colors
#define COLOR2 		255, 252, 25
#define COLOR4 		255, 179, 25
#define COLOR8 		100, 255, 35
#define COLOR16 	100, 162, 104
#define COLOR32 	93, 255, 40
#define COLOR64 	63, 67, 255
#define COLOR128 	188, 67, 255
#define COLOR256 	188, 67, 108
#define COLOR512 	188, 198, 108
#define COLOR1024 	71, 50, 252
#define COLOR2048 	255, 27, 9
#define COLOREMPTY 	189, 189, 189

int 				gscore;
int 				gmove;
int 				gstat;

typedef struct 		s_map
{
	int 			x;
	int 			y;
	int 			value;
	int 			position;
	int 			lock;
	struct s_map	*next;
	struct s_map	*prev;
	struct s_map	*up;
	struct s_map	*down;
}					t_map;

t_map 				*add_val(t_map *map, int pos, int value);
t_map 				*check_left(t_map *map);
t_map 				*fusion_left(t_map *map);
t_map 				*check_right(t_map *map);
t_map 				*fusion_right(t_map *map);
t_map 				*check_down(t_map *map);
t_map 				*fusion_down(t_map *map);
t_map 				*check_up(t_map *map);
t_map 				*fusion_up(t_map *map);
t_map				*move_left(t_map *map);
t_map				*move_right(t_map *map);
t_map				*move_up(t_map *map);
t_map				*move_down(t_map *map);
t_map 				*unlock(t_map *map);
char				*ft_itoa(int n);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strdup(const char *s1);
int 				init(SDL_Window **window, SDL_Surface **screenSurface, SDL_Renderer **renderer);
SDL_Renderer 		*define_color(SDL_Renderer *renderer, int value);
SDL_Renderer 		*print_case(SDL_Renderer *renderer, int value, int xcase, int ycase, TTF_Font *police);
void 				print_map(t_map *map, TTF_Font *police, SDL_Renderer *renderer);

#endif