#include "../cub3d.h"

void	right(t_data *map)
{
	if (map->map[(int)(map->position.pos_x - map->position.dir_vector_y * \
		(map->position.move_speed))][(int)map->position.pos_y] == '0')
		map->position.pos_x -= map->position.dir_vector_y * map->position.move_speed;
	if (map->map[(int)map->position.pos_x][(int)(map->position.pos_y \
	+ map->position.dir_vector_x * (map->position.move_speed))] == '0')
		map->position.pos_y +=map->position.dir_vector_x * map->position.move_speed;
}

void	left(t_data *map)
{
	if (map->map[(int)(map->position.pos_x + map->position.dir_vector_y * \
		(map->position.move_speed))][(int)map->position.pos_y] == '0')
		map->position.pos_x += map->position.dir_vector_y * map->position.move_speed;
	if (map->map[(int)map->position.pos_x][(int)(map->position.pos_y \
	- map->position.dir_vector_x * (map->position.move_speed))] == '0')
		map->position.pos_y -= map->position.dir_vector_x * map->position.move_speed;
}

int	key_press_pos(t_data *map)
{
	if (map->position.forward == 1)
	{
		if (map->map[(int)(map->position.pos_x + map->position.dir_vector_x * map->position.move_speed)]
			[(int)(map->position.pos_y +map->position.dir_vector_y * map->position.move_speed)] == '0')
			if_forward(map);
	}
	if (map->position.back == 1)
	{
		if (map->map[(int)(map->position.pos_x - map->position.dir_vector_x * map->position.move_speed)]
			[(int)(map->position.pos_y - map->position.dir_vector_y * map->position.move_speed)] == '0')
			if_back(map);
	}
	if (map->position.left2 == 1)
		left(map);
	if (map->position.right2 == 1)
		right(map);
	if (map->position.left == 1)
		if_left(map);
	if (map->position.right == 1)
		if_right(map);
	return (0);
}

int	key_press(int keycode, t_data *map)
{
	if (keycode == W)
		map->position.forward = 1;
	else if (keycode == S)
		map->position.back = 1;
	else if (keycode == LEFT)
		map->position.left = 1;
	else if (keycode == RIGHT)
		map->position.right = 1;
	else if (keycode == A)
		map->position.right2 = 1;
	else if (keycode == D)
		map->position.left2 = 1;
	else if (keycode == ESC)
		exit(0);
	return (0);
}

int	key_release(int keycode, t_data *map)
{
	if (keycode == W)
		map->position.forward = 0;
	else if (keycode == S)
		map->position.back = 0;
	else if (keycode == LEFT)
		map->position.left = 0;
	else if (keycode == RIGHT)
		map->position.right = 0;
	else if (keycode == A)
		map->position.right2 = 0;
	else if (keycode == D)
		map->position.left2 = 0;
	return (0);
}
