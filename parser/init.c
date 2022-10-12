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
