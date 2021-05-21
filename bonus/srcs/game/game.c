/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 21:27:11 by dcho              #+#    #+#             */
/*   Updated: 2021/05/20 17:44:30 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	rotation(t_game *g, double degree)
{
	double		rad;
	double		olddirx;
	double		oldplanex;

	if (degree)
	{
		rad = M_PI * degree / 180;
		olddirx = g->dir_x;
		g->dir_x = g->dir_x * cos(rad) - g->dir_y * sin(rad);
		g->dir_y = olddirx * sin(rad) + g->dir_y * cos(rad);
		oldplanex = g->plane_x;
		g->plane_x = g->plane_x * cos(rad) - g->plane_y * sin(rad);
		g->plane_y = oldplanex * sin(rad) + g->plane_y * cos(rad);
	}
}

void	game_main(t_game *g, t_options *op)
{
	init_direction(g);
	init_texture(g);
	init_sprite(g->sprite);
	g->f_color = create_trgb(op->f[0], op->f[1], op->f[2]);
	g->c_color = create_trgb(op->c[0], op->c[1], op->c[2]);
	rotation(g, g->dir);
	load_texture(g, op);
}

int		game_loop(t_game *g)
{
	graphic(g);
	key_update(g, g->map);
	return (0);
}
