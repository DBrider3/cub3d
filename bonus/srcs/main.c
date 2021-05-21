/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 18:12:15 by dcho              #+#    #+#             */
/*   Updated: 2021/05/20 17:45:51 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void		screen_check(t_options op, t_game *g)
{
	int		x;
	int		y;

	mlx_get_screen_size(g->mlx, &x, &y);
	if (op.r[0] > x || op.r[1] > y)
	{
		g->width = x;
		g->height = y;
	}
	else
	{
		g->width = op.r[0];
		g->height = op.r[1];
	}
}

static void		play_music(void)
{
	system("afplay -v -0.30 music/maple_story.mp3 &");
}


static void		start_mlx(t_options *op, t_game *g)
{
	g->mlx = mlx_init();
	screen_check(*op, g);
	game_main(g, op);
	g->win = mlx_new_window(g->mlx, g->width, g->height, "dcho's cub3d");
	g->img.img = mlx_new_image(g->mlx, g->width, g->height);
	g->img.addr = (int*)mlx_get_data_addr(g->img.img, &(g->img.bpp),
					&(g->img.size_l), &(g->img.endian));
	if (g->bmp_flag)
		save_bmp(g);
	else
	{
		play_music();
		mlx_loop_hook(g->mlx, &game_loop, g);
		mlx_hook(g->win, KEY_PRESS, 0, &key_press, g);
		mlx_hook(g->win, KEY_RELEASE, 0, &key_release, g);
		mlx_hook(g->win, 17, 0, exit_btn, 0);
		mlx_loop(g->mlx);
	}
}

int				main(int argc, char *argv[])
{
	t_options	op;
	t_game		game;
	t_sprite	s;
	char		*file_extension;

	if (argc < 2 || argc > 3)
		exit_error("argument number is not appropriate");
	else
	{
		file_extension = argv[1] + (ft_strlen(argv[1]) - 4);
		if (ft_strncmp(file_extension, ".cub", 5))
			exit_error("first argument is not correct");
		if (parse_main(argv[1], &op, &game, &s) == ERROR)
			exit_error("not the correct parsing");
	}
	if (argc == 3)
	{
		game.bmp_flag = 1;
		if (ft_strncmp(argv[2], "--save", ft_strlen(argv[2]) + 1))
			exit_error("second argument is not correct");
	}
	start_mlx(&op, &game);
	final_free(&op, &game);
	return (0);
}
