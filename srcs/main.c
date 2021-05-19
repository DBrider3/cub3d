/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 18:12:15 by dcho              #+#    #+#             */
/*   Updated: 2021/05/19 23:26:58 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

static void	screen_check(t_options op, t_game *g)
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

static void start_mlx(t_options *op, t_game *g)
{
	g->mlx = mlx_init();
	screen_check(*op, g);
	game_main(g, op);
	g->win = mlx_new_window(g->mlx, g->width, g->height, "mlx");
	g->img.img = mlx_new_image(g->mlx, g->width, g->height);
	g->img.addr = (int*)mlx_get_data_addr(g->img.img, &(g->img.bpp),
					&(g->img.size_l), &(g->img.endian));
	mlx_loop_hook(g->mlx, &game_loop, g);
	mlx_hook(g->win, KEY_PRESS, 0, &key_press, g);
	mlx_hook(g->win, KEY_RELEASE, 0, &key_release, g);
	mlx_loop(g->mlx);

}

int		main(int argc, char *argv[])
{
	t_options	op;
	t_game		game;
	t_sprite 	s;

	if (argc != 2)
		exit_error("argument number is not appropriate");
	if (parse_main(argv[1], &op, &game, &s) == ERROR)
		exit_error("not the correct parsing");
	// if (argc == 3 && ft_strncmp(argv[2], "--save", ft_strlen(argv[2])));
	// game.mlx = mlx_init();
	// screen_check(op, &game);
	// game_main(&game, &op);
	// final_free(&op);
	start_mlx(&op, &game);

	return (0);
}


