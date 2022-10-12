#include "../cub3d.h"

int	size_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	pixel_put(int y, int x, t_data *map, unsigned int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 31)
	{
		j = -1;
		while (++j < 31)
			mlx_pixel_put(map->mlx_ptr, map->win_ptr, x + i, y + j, (int)color);
	}
}

int	hex(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	wrapper_init_pos(t_data *map, int *y, int *x)
{
	map->position.pos_x = *y + 0.5;
	map->position.pos_y = *x + 0.5;
	if (map->map[*y][*x] == 'N')
		map->position.dir_vector_x = -1;
	if (map->map[*y][*x] == 'S')
		map->position.dir_vector_x = 1;
	if (map->map[*y][*x] == 'E')
		map->position.dir_vector_y = 1;
	if (map->map[*y][*x] == 'W')
		map->position.dir_vector_y = -1;
	if (map->map[*y][*x] == 'N')
		map->position.plane_y = 0.66;
	if (map->map[*y][*x] == 'S')
		map->position.plane_y = -0.66;
	if (map->map[*y][*x] == 'E')
		map->position.plane_x = 0.66;
	if (map->map[*y][*x] == 'W')
		map->position.plane_x = -0.66;
}

void	init_pos(t_data *map)
{
	int	x;
	int	y;

	y = -1;
	while (++y < size_arr(map->map))
	{
		x = -1;
		while (++x < (int)ft_strlen(map->map[y]))
		{
			if ((ft_strchr("NSEW", map->map[y][x])))
			{
				wrapper_init_pos(map, &y, &x);
				map->map[y][x] = '0';
			}
		}
	}
}
