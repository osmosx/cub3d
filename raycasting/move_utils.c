#include "../cub3d.h"

void	if_forward(t_data *map)
{
	if (map->map[(int)(map->position.pos_x + map->position.dir_vector_x \
		* map->position.move_speed)][(int)(map->position.pos_x)])
		map->position.pos_x += map->position.dir_vector_x * map->position.move_speed;
	if (map->map[(int)(map->position.pos_x)][(int)(map->position.pos_y \
		+ map->position.dir_vector_y * map->position.move_speed)])
		map->position.pos_y += map->position.dir_vector_y * map->position.move_speed;
}

void	if_back(t_data *map)
{
	if (map->map[(int)(map->position.pos_x + map->position.dir_vector_x \
		* map->position.move_speed)][(int)(map->position.pos_y)])
		map->position.pos_x -= map->position.dir_vector_x * map->position.move_speed;
	if (map->map[(int)(map->position.pos_x)][(int)(map->position.pos_y \
		- map->position.dir_vector_y * map->position.move_speed)])
		map->position.pos_y -= map->position.dir_vector_y * map->position.move_speed;
}

void	if_left(t_data *map)
{
	double	old_direction_x;
	double	old_plane_x;

	old_direction_x = map->position.dir_vector_x;
	map->position.dir_vector_x = map->position.dir_vector_x * cos(map->position.rot_speed) \
		- map->position.dir_vector_y * sin(map->position.rot_speed);
	map->position.dir_vector_y = old_direction_x * sin(map->position.rot_speed) \
		+ map->position.dir_vector_y * cos(map->position.rot_speed);
	old_plane_x = map->position.plane_x;
	map->position.plane_x = map->position.plane_x * cos(map->position.rot_speed) \
		- map->position.plane_y * sin(map->position.rot_speed);
	map->position.plane_y = old_plane_x * sin(map->position.rot_speed) \
		+ map->position.plane_y * cos(map->position.rot_speed);
}

void	if_right(t_data *map)
{
	double	old_direction_x;
	double	old_plane_x;

	old_direction_x = map->position.dir_vector_x;
	map->position.dir_vector_x = map->position.dir_vector_x * cos(-map->position.rot_speed) \
		- map->position.dir_vector_y * sin(-map->position.rot_speed);
	map->position.dir_vector_y = old_direction_x * sin(-map->position.rot_speed) \
		+ map->position.dir_vector_y * cos(-map->position.rot_speed);
	old_plane_x = map->position.plane_x;
	map->position.plane_x = map->position.plane_x * cos(-map->position.rot_speed) \
		- map->position.plane_y * sin(-map->position.rot_speed);
	map->position.plane_y = old_plane_x * sin(-map->position.rot_speed) \
		+ map->position.plane_y * cos(-map->position.rot_speed);
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
