#include "../cub3d.h"

void	step(t_data *map)
{
	if (map->draw.ray_dir_x < 0)
	{
		map->draw.step_x = -1;
		map->draw.side_dist_x = (map->position.pos_x - map->draw.map_x) \
				* map->draw.delta_dist_x;
	}
	else
	{
		map->draw.step_x = 1;
		map->draw.side_dist_x = (map->draw.map_x + 1.0 - map->position.pos_x) \
				* map->draw.delta_dist_x;
	}
	if (map->draw.ray_dir_y < 0)
	{
		map->draw.step_y = -1;
		map->draw.side_dist_y = (map->position.pos_y - map->draw.map_y) \
				* map->draw.delta_dist_y;
	}
	else
	{
		map->draw.step_y = 1;
		map->draw.side_dist_y = (map->draw.map_y + 1.0 - map->position.pos_y) \
				* map->draw.delta_dist_y;
	}
}
