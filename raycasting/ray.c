#include "../cub3d.h"

void	wrapper_draw_line(t_data **map)
{
	if ((*map)->draw.side == 0 && (*map)->draw.ray_dir_x < 0)
		(*map)->draw.text = 0;
	if ((*map)->draw.side == 0 && (*map)->draw.ray_dir_x >= 0)
		(*map)->draw.text = 1;
	if ((*map)->draw.side == 1 && (*map)->draw.ray_dir_y < 0)
		(*map)->draw.text = 2;
	if ((*map)->draw.side == 1 && (*map)->draw.ray_dir_y >= 0)
		(*map)->draw.text = 3;
}

void	draw_line(t_data *map)
{
	map->draw.line_h = (int)(WIN_H / map->draw.perp_wall);
	map->draw.draw_start = (-map->draw.line_h / 2) + (WIN_H / 2);
	if (map->draw.draw_start < 0)
		map->draw.draw_start = 0;
	map->draw.draw_end = (map->draw.line_h / 2) + (WIN_H / 2);
	if (map->draw.draw_end >= WIN_H || map->draw.draw_end < 0)
		map->draw.draw_end = WIN_H - 1;
	map->draw.tex_num = map->map[map->draw.map_x][map->draw.map_y];
	wrapper_draw_line(&map);
	if (map->draw.side == 0)
		map->draw.wall_x = map->position.pos_y + map->draw.perp_wall \
				* map->draw.ray_dir_y;
	else
		map->draw.wall_x = map->position.pos_x + map->draw.perp_wall \
				* map->draw.ray_dir_x;
	map->draw.wall_x -= floor(map->draw.wall_x);
	map->draw.tex_x = (int)(map->draw.wall_x * (double)TEX_W);
	if (map->draw.side == 0 && map->draw.ray_dir_x > 0)
		map->draw.tex_x = TEX_W - map->draw.tex_x - 1;
	if (map->draw.side == 1 && map->draw.ray_dir_y < 0)
		map->draw.tex_x = TEX_W - map->draw.tex_x - 1;
	map->draw.step = 1.0 * TEX_H / map->draw.line_h;
	map->draw.tex_pos = (map->draw.draw_start - WIN_H \
		/ 2 + map->draw.line_h / 2) * map->draw.step;
}

void	hit(t_data *map)
{
	map->draw.hit = 0;
	while (map->draw.hit == 0)
	{
		if (map->draw.side_dist_x < map->draw.side_dist_y)
		{
			map->draw.side_dist_x += map->draw.delta_dist_x;
			map->draw.map_x += map->draw.step_x;
			map->draw.side = 0;
		}
		else
		{
			map->draw.side_dist_y += map->draw.delta_dist_y;
			map->draw.map_y += map->draw.step_y;
			map->draw.side = 1;
		}
		if (map->map[map->draw.map_x][map->draw.map_y] == '1')
			map->draw.hit = 1;
	}
	if (map->draw.side == 0)
		map->draw.perp_wall = ((double)map->draw.map_x - map->position.pos_x \
			+ (1 - (double)map->draw.step_x) / 2) / map->draw.ray_dir_x;
	else
		map->draw.perp_wall = ((double)map->draw.map_y - map->position.pos_y \
			+ (1 - (double)map->draw.step_y) / 2) / map->draw.ray_dir_y;
}

void	wrapper_calc_and_save(t_data **map, int *x)
{
	(*map)->draw.camera_x = 2 * (*x) / (double)(WIN_W) - 1;
	(*map)->draw.ray_dir_x = (*map)->position.dir_vector_x \
		+ (*map)->position.plane_x *(*map)->draw.camera_x;
	(*map)->draw.ray_dir_y = (*map)->position.dir_vector_y \
		+ (*map)->position.plane_y * (*map)->draw.camera_x;
	(*map)->draw.map_x = (int)(*map)->position.pos_x;
	(*map)->draw.map_y = (int)(*map)->position.pos_y;
	(*map)->draw.delta_dist_x = fabs(1 / (*map)->draw.ray_dir_x);
	(*map)->draw.delta_dist_y = fabs(1 / (*map)->draw.ray_dir_y);
}

int	calc_and_save(t_data *map)
{
	int	x;
	int	color;

	x = 0;
	while (x < WIN_W)
	{
		wrapper_calc_and_save(&map, &x);
		step(map);
		hit(map);
		draw_line(map);
		while (map->draw.draw_start < map->draw.draw_end)
		{
			map->draw.tex_y = (int)map->draw.tex_pos % TEX_H;
			map->draw.tex_pos += map->draw.step;
			color = map->texture.texture[map->draw.text] \
					[TEX_H * map->draw.tex_y + map->draw.tex_x];
			if (map->draw.side == 1)
				color = (color >> 1) & 8355711;
			map->buf[map->draw.draw_start][x] = color;
			map->draw.draw_start++;
		}
		x++;
	}
	key_press_pos(map);
	return (0);
}
