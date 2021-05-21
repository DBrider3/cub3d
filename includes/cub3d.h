/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 18:06:04 by dcho              #+#    #+#             */
/*   Updated: 2021/05/20 17:43:15 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <math.h>
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"

# define ERROR -1
# define NO_ERROR 0
# define INITAIL_SIZE 8
# define FULLFLAG " 012EWSN"
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
# define U_DIV 1
# define V_DIV 1
# define V_MOVE 0.0
# define KEY_PRESS 2
# define KEY_RELEASE 3
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define K_A 0
# define K_S 1
# define K_D 2
# define K_W 13
# define K_ESE 53

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
	double			sprite_x;
	double			sprite_y;
	double			invdet;
	double			trans_x;
	double			trans_y;
	double			screen_x;
	int				vm_screen;
	int				sprite_height;
	int				draw_start_x;
	int				draw_end_x;
	int				draw_start_y;
	int				draw_end_y;
	int				sprite_width;
	int				tex_x;
	int				tex_y;
	int				d;
	int				color;
}					t_sprite;

typedef struct		s_game
{
	void			*mlx;
	void			*win;
	double			dir;
	int				width;
	int				height;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
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
	int				bmp_flag;
	t_img			img;
	double			*zbuf;
	t_map			*map;
	t_sprite		*sprite;
}					t_game;

typedef struct		s_raycast
{
	double			camera_x;
	double			raydir_x;
	double			raydir_y;
	int				map_x;
	int				map_y;
	double			sd_x;
	double			sd_y;
	double			dd_x;
	double			dd_y;
	int				step_x;
	int				step_y;
	int				side;
	int				l_height;
	int				tex_num;
	int				draw_start;
	int				draw_end;
	double			pwd;
	double			wall_x;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;
	int				color;
}					t_raycast;

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

/*
**	init part
*/
void				init_start(t_options *op, t_game *g, t_sprite *s);
void				init_sprite(t_sprite *s);
void				init_direction(t_game *g);
void				init_texture(t_game *g);
/*
**	error part
*/
int					exit_error(char *s);
int					exit_btn(void);
/*
**	free part
*/
void				final_free(t_options *op, t_game *g);
int					free_inside(char **input);
int					free_value(void *ptr);
/*
**	parsing part
*/
int					parse_main(char *f, t_options *op, t_game *g, t_sprite *s);
int					parse_identifier(char *line, t_options *op);
int					input_fc(char **input, t_options *op, int flag);
int					input_file_one(char **input, t_options *op, int flag);
int					input_file_two(char **input, t_options *op, int flag);
int					input_r(char **input, t_options *op);
int					check_size(char **input);
int					check_identifier(t_options op);
int					new_map(t_map **m);
int					add_map_line(t_map *m, char *line);
void				del_map(t_map *m);
int					find_map(char *line, int *flag, t_options *op);
void				map_check_main(t_map *m, t_game *g);
void				check_duplication_one(t_options *op, int flag);
void				check_duplication_two(t_options *op, int flag);
/*
**	graphic part
*/
void				rotation(t_game *g, double degree);
void				game_main(t_game *g, t_options *op);
int					game_loop(t_game *g);
void				raycasting_main(t_game *g);
void				graphic(t_game *info);
void				draw_color(t_game *g, int x, int color, int section);
void				sprite_main(t_game *g, t_sprite *s);
void				draw_texture(t_game *g, t_raycast *rc, int x);
void				draw_sprite(t_game *g, t_sprite *s);
void				game_display(t_game *g);
void				load_texture(t_game *g, t_options *op);
void				load_image(t_game *g, int *texture, char *path, t_img *img);
int					key_press(int key, t_game *g);
int					key_release(int key, t_game *g);
void				key_update(t_game *g, t_map *m);
int					create_trgb(int r, int g, int b);
void				save_bmp(t_game *g);

#endif
