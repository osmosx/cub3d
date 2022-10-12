#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include "libmlx/mlx.h"
# include "./libft/libft.h"

# define WIN_W 1200
# define WIN_H 800
# define TEX_H 1024
# define TEX_W 1024

# define BUFFER_SIZE 	1
# define KEY_PRESS 		2
# define KEY_RELEASE 	3
# define KEY_EXIT		17

# define W 				13
# define A 				0
# define D 				2
# define S 				1
# define ESC 			53
# define UP				126
# define DOWN			125
# define LEFT			123
# define RIGHT			124

typedef struct s_img
{
	void	*img;
	int		*data;
	int		size;
	int		bits_per_pixel;
	int		endian;
	int		h;
	int		w;
}	t_img;

typedef struct s_texture
{
	int		**texture;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		ceiling[3];
	int		floor[3];
}	t_texture;

typedef struct s_position
{
	double		move_speed;
	double		rot_speed;
	int			forward;
	int			back;
	int			left;
	int			right;
	int			right2;
	int			left2;
	double		dir_vector_x;
	double		dir_vector_y;
	double		pos_x;
	double		pos_y;
	double		plane_x;
	double		plane_y;

}	t_position;

typedef struct s_draw
{
	int			side;
	int			text;
	int			line_h;
	int			draw_start;
	int			draw_end;
	int			map_x;
	int			map_y;
	int			tex_num;
	double		camera_x;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		step;
	int			step_x;
	int			step_y;
	double		perp_wall;
	double		ray_dir_x;
	double		ray_dir_y;
	double		tex_pos;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	int			hit;

}	t_draw;

typedef struct s_data
{
	char		*addr;
	char		*mlx_ptr;
	char		*win_ptr;
	int			line_length;
	int			endian;
	char		**map;
	int			buf[WIN_H][WIN_W];
	t_img		img;
	t_texture	texture;
	t_position 	position;
	t_draw 		draw;
}				t_data;

void		image_draw(t_data *map);

//Raycasting
void		init(t_data *map);
void		init_pos(t_data *map);
int			find_player(t_data *map);
void		ceiling_floor(t_data *map);
int			calc_and_save(t_data *map);
int			key_press_pos(t_data *map);
void		step(t_data *map);

//Parser
void		parser(t_data *map, char *file);
void		check_file(char *file);
void		check_map_info(char **split_file);
void		record_file_info(char **split_file, t_data *map);
void		reading_a_file(char ***split_file, int fd, char *file);
void		map_size(t_data *map);
void		error_read(int rd);
void		load_texture(t_data *map);
int			init_texture(t_data *map);
//Utils
int			main_loop(t_data *map);
int			keyup(int key, t_data *map);
int			keydown(int key, t_data *map);
int			handle_no_event(void *map);
void		free_matrix(char **str);
void		print_error(char *s1, char *s2, char *s3, char *s4);
int			hex(int r, int g, int b);
int			key_release(int keycode, t_data *map);
int			key_press(int keycode, t_data *map);
int			mouse_move(int x, int y, t_data *map);
int			ft_exit(t_data *map);
void		if_left(t_data *map);
void		if_right(t_data *map);
void		if_forward(t_data *map);
void		if_back(t_data *map);
#endif