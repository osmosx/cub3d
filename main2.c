/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medeana <medeana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:15:30 by medeana           #+#    #+#             */
/*   Updated: 2022/05/04 18:19:58 by medeana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	mouse_move(int x, int y, t_cub *cub)
{
	static int	old_x;

	if (x <= SWIGHT && x >= 0 && y <= SHEIGHT && y >= 0)
	{
		if (x < old_x)
			if_left(cub);
		else if (x > old_x)
			if_right(cub);
	}
	old_x = x;
	return (0);
}

int	ft_exit(t_cub *cub)
{
	(void)cub;
	exit(0);
}

int	main(int ac, char **av)
{
	t_cub	cub;

	if (ac != 2)
		print_error("Probably the number of arguments\n", NULL, NULL, NULL);
	parser(&cub, av[1]);
	cub.mlx = mlx_init();
	init(&cub);
	init_texture(&cub);
	load_texture(&cub);
	cub.win = mlx_new_window(cub.mlx, SWIGHT, SHEIGHT, "mlx");
	cub.img.img = mlx_new_image(cub.mlx, SWIGHT, SHEIGHT);
	cub.img.data = (int *)mlx_get_data_addr(cub.img.img, \
		&cub.img.bpp, &cub.img.size, &cub.img.endian);
	mlx_hook(cub.win, 2, 1L << 0, &key_press, &cub);
	mlx_hook(cub.win, 6, 0, mouse_move, &cub);
	mlx_hook(cub.win, 17, 0, ft_exit, &cub);
	mlx_loop_hook(cub.mlx, &main_loop, &cub);
	mlx_hook(cub.win, 3, 1L << 1, &key_release, &cub);
	mlx_loop(cub.mlx);
}
