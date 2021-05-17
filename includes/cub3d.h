/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 18:06:04 by dcho              #+#    #+#             */
/*   Updated: 2021/05/18 06:05:55 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "get_next_line.h"
#include "libft.h"
#include "mlx.h"

# define ERROR -1
# define NO_ERROR 0
# define INITAIL_SIZE 8
# define FULLFLAG " 012EWSN"
# define MAPFLAG "012EWSN"
# define POS "EWSN"
# define RFLAG 1
# define NOFLAG 2
# define SOFLAG 4
# define WEFLAG 8
# define EAFLAG 16
# define SFLAG 32
# define FFLAG 64
# define CFLAG 128
# define POSFLAG 256
/*
그래픽 부분
*/

#include <math.h>

# define KEY_PRESS 2
# define KEY_RELEASE 3
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
// # define mapWidth 24
// # define mapHeight 24
# define K_A 0
# define K_S 1
# define K_D 2
# define K_W 13
# define K_ESE 53
// #define width 640
// #define height 480

typedef struct		s_img
{
    void			*img;
    int				*addr;
    int				bpp;
    int				size_l;
    int				endian;
    int				img_width;
	int				img_height;
}					t_img;

typedef struct		s_map
{
	char			**map;
	int				index;
	int				size;
	int				max_col;
}					t_map;

typedef struct		s_sprite
{
	int				num;
	double			**loc_sprite;
	double			*sprite_dist;
}					t_sprite;

typedef struct		s_game
{
	void			*mlx;
	void			*win;
	double			dir;
	int				width;
	int				height;
	double			pos_x;
	double 			pos_y;
	double 			dir_x;
	double 			dir_y;
	double 			plane_x;
	double 			plane_y;
	int				**texture;
	double			movespeed;
	double			rotspeed;
	int				key_a;
	int				key_w;
	int				key_s;
	int				key_d;
	int				ket_esc;
	int				f_color;
	int				c_color;
	t_img			img;
	t_map			*map;
	t_sprite		*sprite;
}					t_game;

typedef struct		s_raycast
{
	double			camera_x; //
	double			raydir_x; //
	double			raydir_y; //
	int				map_x; //
	int				map_y; //
	double			sd_x; //
	double			sd_y; //
	double			dd_x; //
	double			dd_y; //
	int				step_x; //
	int				step_y; //
	// int				hit; //
	int				side; //
	int				l_height; //
	int				tex_num; //
	int				draw_start; //
	int				draw_end; //
	double				pwd; //
	double			wall_x; //
	int				tex_x; //
	int				tex_y; //
	double			step; //
	double			tex_pos; //
	int				color; //
}					t_raycast;


// typedef struct		s_calc
// {

// }


int		exit_error(char *s);
/*
그래픽 추가 끝
*/


typedef struct		s_options
{
	int				r[2];
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*s;
	int				f[3];
	int				c[3];
	t_map			*map;
	int				flags;
}					t_options;



int					parse_main(char *f, t_options *op, t_game *g, t_sprite *s);
// int					parse_main(char *f, t_options *op, t_game *g);
void				init_start(t_options *op, t_game *g, t_sprite *s);
void				init_sprite(t_sprite *s);
int					parse_identifier(char *line, t_options *op);
int					input_fc(char **input, t_options *op, int flag);
int					input_file_one(char **input, t_options *op, int flag);
int					input_file_two(char **input, t_options *op, int flag);
int					input_r(char **input, t_options *op);
int					check_size(char **input);
int					free_inside(char **input);
int			 		free_value(void *ptr);
int					check_identifier(t_options op);
int					new_map(t_map **m);
int					add_map_line(t_map *m, char *line);
void				del_map(t_map *m);
int					find_map(char *line, int *flag, t_options *op);
void				map_check_main(t_map *m, t_game *g, t_sprite *s);
void				check_duplication_one(t_options *op, int flag);
void				check_duplication_two(t_options *op, int flag);
void				final_free(t_options *op);
void				init_direction(t_game *g);
void				game_init_allocation(t_game *g);
void				rotation(t_game *g, double degree);
void		game_main(t_game *g, t_options *op);
// void		game_main(t_game *g);

int					game_loop(t_game *g);

void	load_texture(t_game *g, t_options *op);
void	load_image(t_game *g, int *texture, char *path, t_img *img);
int		key_press(int key, t_game *g);
int		key_release(int key, t_game *g);
// void	draw(t_game *info);
void	key_update(t_game *g, t_map *m);
void	calc(t_game *info);
// void	calc(t_game *info, t_raycast *rc);
int	create_trgb(int r, int g, int b);
#endif
