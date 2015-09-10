#ifndef INC_H
# define INC_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 		650
#define HEIGHT 		650

int 				gscore;
int 				gmove;

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
void 				print_map(t_map *map);

#endif