/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medeana <medeana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:57:33 by medeana           #+#    #+#             */
/*   Updated: 2022/05/03 21:02:47 by medeana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	wrapper_draw_line(t_cub **cub)
{
	if ((*cub)->side == 0 && (*cub)->ray_dir_x < 0)
		(*cub)->text = 0;
	if ((*cub)->side == 0 && (*cub)->ray_dir_x >= 0)
		(*cub)->text = 1;
	if ((*cub)->side == 1 && (*cub)->ray_dir_y < 0)
		(*cub)->text = 2;
	if ((*cub)->side == 1 && (*cub)->ray_dir_y >= 0)
		(*cub)->text = 3;
}

void	draw_line(t_cub *cub)
{
	cub->line_h = (int)(SHEIGHT / cub->perp_wall);
	cub->draw_start = (-cub->line_h / 2) + (SHEIGHT / 2);
	if (cub->draw_start < 0)
		cub->draw_start = 0;
	cub->draw_end = (cub->line_h / 2) + (SHEIGHT / 2);
	if (cub->draw_end >= SHEIGHT || cub->draw_end < 0)
		cub->draw_end = SHEIGHT - 1;
	cub->tex_num = cub->map[cub->map_x][cub->map_y];
	wrapper_draw_line(&cub);
	if (cub->side == 0)
		cub->wall_x = cub->pos_y + cub->perp_wall * cub->ray_dir_y;
	else
		cub->wall_x = cub->pos_x + cub->perp_wall * cub->ray_dir_x;
	cub->wall_x -= floor(cub->wall_x);
	cub->tex_x = (int)(cub->wall_x * (double)TEXW);
	if (cub->side == 0 && cub->ray_dir_x > 0)
		cub->tex_x = TEXW - cub->tex_x - 1;
	if (cub->side == 1 && cub->ray_dir_y < 0)
		cub->tex_x = TEXW - cub->tex_x - 1;
	cub->step = 1.0 * TEXH / cub->line_h;
	cub->tex_pos = (cub->draw_start - SHEIGHT \
		/ 2 + cub->line_h / 2) * cub->step;
}

void	hit(t_cub *cub)
{
	cub->hit = 0;
	while (cub->hit == 0)
	{
		if (cub->side_dist_x < cub->side_dist_y)
		{
			cub->side_dist_x += cub->delta_dist_x;
			cub->map_x += cub->step_x;
			cub->side = 0;
		}
		else
		{
			cub->side_dist_y += cub->delta_dist_y;
			cub->map_y += cub->step_y;
			cub->side = 1;
		}
		if (cub->map[cub->map_x][cub->map_y] == '1')
			cub->hit = 1;
	}
	if (cub->side == 0)
		cub->perp_wall = ((double)cub->map_x - cub->pos_x \
			+ (1 - (double)cub->step_x) / 2) / cub->ray_dir_x;
	else
		cub->perp_wall = ((double)cub->map_y - cub->pos_y \
			+ (1 - (double)cub->step_y) / 2) / cub->ray_dir_y;
}

void	wrapper_calc_and_save(t_cub **cub, int *x)
{
	(*cub)->camera_x = 2 * (*x) / (double)(SWIGHT) - 1;
	(*cub)->ray_dir_x = (*cub)->dir_vector_x \
		+ (*cub)->plane_x * (*cub)->camera_x;
	(*cub)->ray_dir_y = (*cub)->dir_vector_y \
		+ (*cub)->plane_y * (*cub)->camera_x;
	(*cub)->map_x = (int)(*cub)->pos_x;
	(*cub)->map_y = (int)(*cub)->pos_y;
	(*cub)->delta_dist_x = fabs(1 / (*cub)->ray_dir_x);
	(*cub)->delta_dist_y = fabs(1 / (*cub)->ray_dir_y);
}

int	calc_and_save(t_cub *cub)
{
	int	x;
	int	color;

	x = 0;
	while (x < SWIGHT)
	{
		wrapper_calc_and_save(&cub, &x);
		step(cub);
		hit(cub);
		draw_line(cub);
		while (cub->draw_start < cub->draw_end)
		{
			cub->tex_y = (int)cub->tex_pos % TEXH;
			cub->tex_pos += cub->step;
			color = cub->texture[cub->text][TEXH * cub->tex_y + cub->tex_x];
			if (cub->side == 1)
				color = (color >> 1) & 8355711;
			cub->buf[cub->draw_start][x] = color;
			cub->draw_start++;
		}
		x++;
	}
	ft_key_press(cub);
	return (0);
}
