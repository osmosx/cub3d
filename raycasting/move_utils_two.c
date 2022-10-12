#include "../cub3d.h"

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

int	main_loop(t_data *map)
{
	ceiling_floor(map);
	calc_and_save(map);
	image_draw(map);
	return (0);
}