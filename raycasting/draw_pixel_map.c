/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medeana <medeana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:39:55 by medeana           #+#    #+#             */
/*   Updated: 2022/05/04 16:45:12 by medeana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	size_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	ft_pixel_put(int y, int x, t_cub *cub, unsigned int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 31)
	{
		j = -1;
		while (++j < 31)
			mlx_pixel_put(cub->mlx, cub->win, x + i, y + j, (int)color);
	}
}

int	ft_hex(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	wrapper_init_pos(t_cub *cub, int *y, int *x)
{
	cub->pos_x = *y + 0.5;
	cub->pos_y = *x + 0.5;
	if (cub->map[*y][*x] == 'N')
		cub->dir_vector_x = -1;
	if (cub->map[*y][*x] == 'S')
		cub->dir_vector_x = 1;
	if (cub->map[*y][*x] == 'E')
		cub->dir_vector_y = 1;
	if (cub->map[*y][*x] == 'W')
		cub->dir_vector_y = -1;
	if (cub->map[*y][*x] == 'N')
		cub->plane_y = 0.66;
	if (cub->map[*y][*x] == 'S')
		cub->plane_y = -0.66;
	if (cub->map[*y][*x] == 'E')
		cub->plane_x = 0.66;
	if (cub->map[*y][*x] == 'W')
		cub->plane_x = -0.66;
}

void	init_pos(t_cub *cub)
{
	int	x;
	int	y;

	y = -1;
	while (++y < size_arr(cub->map))
	{
		x = -1;
		while (++x < ft_strlen(cub->map[y]))
		{
			if ((ft_strchr("NSEW", cub->map[y][x])))
			{
				wrapper_init_pos(cub, &y, &x);
				cub->map[y][x] = '0';
			}
		}
	}
}
