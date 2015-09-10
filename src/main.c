#include "inc.h"

t_map 	*unlock(t_map *map)
{
	t_map *head;

	head = map;
	while (head)
	{
		head->lock = 0;
		head = head->next;
	}
	return (map);
}

int 	status_game(t_map *map)
{
	t_map 	*head;
	int 	i;

	head = map;
	i = 0;
	while (head->next)
	{
		if (head->value < 0)
			i++;
		head = head->next;
	}
	return (gscore >= 2048 ? 0 : i);
}

int 	check_free_place(t_map *map)
{
	t_map	*head;
	int 	pos;
	int 	i;

	head = map;
	i = 0;
	srand(time(NULL));
	pos = (rand() % 2);
	while (head->next)
	{
		if (pos && (head->value < 0) && (i++ > (rand() % 3)))
			return (head->position);
		head = head->next;
	}
	i = 0;
	while (head && (head->value >= 0)  && (i++ > (rand() % 3)))
		head = head->prev;
	return (head->position);
}

t_map 	*put_rand_value(t_map *map, int pos)
{
	t_map 		*head;

	head = map;
	while (head->position != pos)
		head = head->next;
	if (head->value >= 0)
		return (put_rand_value(map, pos - 1));
	else
		head->value = (rand() % 2 == 0 ? 2 : 4);
	return (map);
}

void 	print_map(t_map *map)
{
	int i;

	i = 0;
	while (map)
	{
		if (map->value < 0)
			printf("[-]");
		else
			printf("[%d]", map->value);
		if (i++ == 3)
		{
			printf("\n");
			i = 0;
		}
		else
			printf("%s", map->value > 9 ? "  " : " ");
		map = map->next;
	}
}

t_map 	*find_down(t_map *map)
{
	t_map *head;

	head = map;
	while (head && head->position != (map->position + 4))
		head = head->next;
	return (head);
}

t_map 	*find_up(t_map *map)
{
	t_map *head;

	head = map;
	while (head && head->position != (map->position - 4))
		head = head->prev;
	return (head);
}

t_map 	*link_upndown(t_map *map)
{
	t_map *head;

	head = map;
	while (head)
	{
		head->down = find_down(head);
		head->up = find_up(head);
		head = head->next;
	}
	return (map);
}

t_map 	*lst_add(t_map *map, int rand_val, int rand_pos)
{
	t_map *new_map;
	t_map *head_map;
	static int position;
	static int y;
	static int x;

	rand_val = (rand_val <= 9 ? 2 : 4);
	new_map = (t_map *)malloc(sizeof(t_map));
	new_map->position = position;
	new_map->y = y;
	new_map->x = x;
	new_map->value = rand_pos < 0 ? -1 : rand_val;
	new_map->lock = 0;
	new_map->next = NULL;
	new_map->prev = NULL;
	new_map->up = NULL;
	new_map->down = NULL;
	position += 1;
	x++;
	if (x == 4)
	{
		x = 0;
		y++;
	}
	head_map = map;
	if (map != NULL)
	{
		while (head_map->next)
			head_map = head_map->next;
		new_map->prev = head_map;
		head_map->next = new_map;
	}
	else
		return (new_map);
	return (map);
}

int 	*rand_position(void)
{
	int *tab;

	tab = (int *)malloc(sizeof(int) * 4);
	srand(time(NULL));
	tab[0] = rand() % 10;
	tab[1] = rand() % 16;
	tab[2] = rand() % 10;
	while ((tab[3] = rand() % 16) == tab[1])
		;
	tab[4] = 0;
	return tab;
}

t_map 	*create_map(t_map *map)
{
	int *tab;
	int i;

	i = 0;
	tab = rand_position();
	while (i < 16)
	{
		if (i == tab[1])
			map = lst_add(map, tab[0], tab[1]);
		else if (i == tab[3])
			map = lst_add(map, tab[2], tab[3]);
		else
			map = lst_add(map, -1, -1);
		i++;
	}
	map = link_upndown(map);
	free(tab);
	return map;
}

int 	main(void)
{
	t_map	*map;
	char 	str[20];

	gscore = 0;
	map = NULL;
	map = create_map(map);
	while (42)
	{
		print_map(map);
		scanf("%s", str);
		if (str[0] == 'z')
			map = move_up(fusion_up(unlock(map)));
		else if (str[0] == 'q')
			map = move_left(fusion_left(unlock(map)));
		else if (str[0] == 's')
			map = move_right(fusion_right(unlock(map)));
		else if (str[0] == 'w')
			map = move_down(fusion_down(unlock(map)));
		if (gmove)
			put_rand_value(map, check_free_place(map));
		gmove = 0;
		if (!status_game(map))
			break;
		printf("SCORE: %d\n", gscore);
	}

	printf("%s\n", (gscore >= 2048 ? "Bravo" : "Game-over"));
	return (0);
}