/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenvoy <nenvoy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:00:47 by nenvoy            #+#    #+#             */
/*   Updated: 2022/10/16 18:00:48 by nenvoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init(t_data *map)
{
	init_pos(map);
	map->position.move_speed = 0.05;
	map->position.rot_speed = 0.05;
	map->position.back = 0;
	map->position.forward = 0;
	map->position.left = 0;
	map->position.right = 0;
	map->position.left2 = 0;
	map->position.right2 = 0;
}

void	checking_the_extension(char *file)
{
	int	i;

	i = (ft_strlen(file)) - 4;
	if (ft_strncmp(".cub\0", file + i, 4))
	{
		print_error("Incorrect file extension: ", file, "\n", NULL);
		exit(EXIT_FAILURE);
	}
}
