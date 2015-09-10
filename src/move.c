#include "inc.h"

t_map 	*add_val(t_map *map, int pos, int value)
{
	t_map *head;

	head = map;
	while (head)
	{
		if (head->position == pos)
		{
			head->value = value;
			if (value >= 0)
			{
				head->lock = 1;
				gscore += (value / 2);
				gmove = 1;
			}
			break;
		}
		head = head->next;
	}
	return (map);
}

t_map 	*check_left(t_map *map)
{
	t_map 	*head;
	int 	rec;

	head = map;
	rec = 0;
	while (head && (head->y == map->y) && (head->prev && head->prev->y == map->y))
	{
		head = head->prev;
		if (head && (head->value == map->value) && !head->lock)
		{
			head = add_val(head, head->position, (head->value + map->value));
			head = add_val(head, map->position, -1);
			rec = 1;
			break;
		}
		else if (head && (((head->value != map->value) && (head->value != -1)) || (head->value == map->value && head->lock)))
			break;
	}
	return (rec ? check_left(map) : map);
}

t_map 	*fusion_left(t_map *map)
{
	t_map *head;

	head = map;
	while (head)
	{
		if (head->value >= 0)
			head = check_left(head);
		head = head->next;
	}
	return (map);
}

t_map 	*check_right(t_map *map)
{
	t_map 	*head;
	int 	rec;

	head = map;
	rec = 0;
	while (head && (head->y == map->y) && (head->prev && head->prev->y == map->y))
	{
		head = head->prev;
		if (head && (head->value == map->value) && !head->lock)
		{
			head = add_val(head, map->position, (head->value + map->value));
			head = add_val(head, head->position, -1);
			rec = 1;
			break;
		}
		else if (head && (((head->value != map->value) && (head->value != -1)) || (head->value == map->value && head->lock)))
			break;
	}
	return (rec ? check_right(map) : map);
}

t_map 	*fusion_right(t_map *map)
{
	t_map *head;

	head = map;
	while (head->next)
		head = head->next;
	while (head)
	{
		if (head->value >= 0)
			head = check_right(head);
		head = head->prev;
	}
	return (map);
}

t_map 	*check_up(t_map *map)
{
	t_map 	*head;
	int 	rec;

	head = map;
	rec = 0;
	while (head && head->prev)
	{
		head = head->prev;
		if (head && (head->x == map->x) && (head->value == map->value) && !head->lock)
		{
			head = add_val(head, head->position, (head->value + map->value));
			head = add_val(head, map->position, -1);
			rec = 1;
			break;
		}
		else if (head && (head->x == map->x) && (((head->value != map->value) && (head->value != -1)) || (head->value == map->value && head->lock)))
			break;
	}
	return (rec ? check_up(map) : map);
}

t_map 	*fusion_up(t_map *map)
{
	t_map *head;

	head = map;
	while (head)
	{
		if (head->value >= 0)
			head = check_up(head);
		head = head->next;
	}
	return (map);
}

t_map 	*check_down(t_map *map)
{
	t_map 	*head;
	int 	rec;

	head = map;
	rec = 0;
	while (head && head->prev)
	{
		head = head->prev;
		if (head && (head->x == map->x) && (head->value == map->value) && !head->lock)
		{
			head = add_val(head, map->position, (head->value + map->value));
			head = add_val(head, head->position, -1);
			rec = 1;
			break;
		}
		else if (head && (head->x == map->x) && (((head->value != map->value) && (head->value != -1)) || (head->value == map->value && head->lock)))
			break;
	}
	return (rec ? check_down(map) : map);
}

t_map 	*fusion_down(t_map *map)
{
	t_map *head;

	head = map;
	while (head->next)
		head = head->next;
	while (head)
	{
		if (head->value >= 0)
			head = check_down(head);
		head = head->prev;
	}
	return (map);
}

t_map *move_left(t_map *map)
{
	t_map 	*head;
	int 	rec;

	head = map;
	rec = 0;
	while (head)
	{
		if ((head->value >= 0) && head->prev && (head->prev->value < 0) && (head->prev->y == head->y))
		{
			head->prev->value = head->value;
			head->value = -1;
			rec = 1;
			gmove = 1;
		}
		head = head->next;
	}
	return (rec ? move_left(map) : map);
}

t_map *move_right(t_map *map)
{
	t_map 	*head;
	int 	rec;

	head = map;
	rec = 0;
	while (head->next)
		head = head->next;
	while (head)
	{
		if ((head->value >= 0) && head->next && (head->next->value < 0) && (head->next->y == head->y))
		{
			head->next->value = head->value;
			head->value = -1;
			rec = 1;
			gmove = 1;
		}
		head = head->prev;
	}
	return (rec ? move_right(map) : map);
}

t_map *move_up(t_map *map)
{
	t_map 	*head;
	int 	rec;

	head = map;
	rec = 0;
	while (head)
	{
		if ((head->value >= 0) && head->up && (head->up->value < 0))
		{
			head->up->value = head->value;
			head->value = -1;
			rec = 1;
			gmove = 1;
		}
		head = head->next;
	}
	return (rec ? move_up(map) : map);
}

t_map *move_down(t_map *map)
{
	t_map 	*head;
	int 	rec;

	head = map;
	rec = 0;
	while (head->next)
		head = head->next;
	while (head)
	{
		if ((head->value >= 0) && head->down && (head->down->value < 0))
		{
			head->down->value = head->value;
			head->value = -1;
			rec = 1;
			gmove = 1;
		}
		head = head->prev;
	}
	return (rec ? move_down(map) : map);
}