#include "cub3d.h"

int	main(int ac, char **av)
{
	t_data 	map;

	if (ac != 2)
		print_error("Probably the number of arguments\n", NULL, NULL, NULL);
	parser(&map, av[1]);
	map.mlx_ptr = mlx_init();
	init(&map);
	init_texture(&map);
	load_texture(&map);
	map.win_ptr = mlx_new_window(map.mlx_ptr, WIN_W, WIN_H, "cub3d");
	map.img.img = mlx_new_image(map.mlx_ptr, WIN_W, WIN_H);
	map.img.data = (int *)mlx_get_data_addr(map.img.img, &map.img.bits_per_pixel, &map.line_length,
											&map.img.endian);
	mlx_hook(map.win_ptr, 2, 0, &key_press, &map);
	mlx_hook(map.win_ptr, 3, 0, &key_release, &map);
	mlx_hook(map.win_ptr, 6, 0, mouse_move, &map);
	mlx_hook(map.win_ptr, 17, 0, ft_exit, &map);
	mlx_loop_hook(map.mlx_ptr, &main_loop, &map);
	mlx_loop(map.mlx_ptr);
}
