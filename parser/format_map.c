#include "../cub3d.h"

//void	*ft_calloc(size_t count) //Count длина выделенной памяти (ширина на длину)
//{
//	void	*ptr;
//
//	ptr = malloc (count);
//	ptr[count - 1] = '\0';
//	if (!ptr)
//		return (0);
//	ft_memset (ptr, '.', count - 1); //Вместо нуля то  чем заполнить
//}


void	map_size(t_data *map)
{
	int		i;
	int		l;
	size_t	weight;

	i = 0;
	l = 0;
	weight = 0;
	while (map->map[i])
	{
		if (ft_strlen(map->map[i]) > weight)
		{
			weight = ft_strlen(map->map[i]);
			map->img.w = weight;
		}
		i++;
	}
	map->img.h = i - 1;
}