/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 21:27:11 by dcho              #+#    #+#             */
/*   Updated: 2021/05/15 21:31:48 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	rotation(t_game *g, double degree)
{
	double		rad;
	double		olddirx;
	double		oldplanex;

	if (degree)
	{
		rad = M_PI * degree / 180;
		olddirx = g->dirx;
		g->dirx = g->dirx * cos(rad) - g->diry * sin(rad);
		g->diry = olddirx * sin(rad) + g->diry * cos(rad);
		oldplanex = g->planex;
		g->planex = g->planex * cos(rad) - g->planey * sin(rad);
		g->planey = oldplanex * sin(rad) + g->planey * cos(rad);
	}
}

void		game_main(t_game *g, t_options *op)
{
	init_direction(g);
	g->f_color = create_trgb(op->f[0],op->f[1],op->f[2]);
	g->c_color = create_trgb(op->c[0],op->c[1],op->c[2]);
	rotation(g, g->dir);
	game_init_allocation(g);
	load_texture(g, op);
}

int		game_loop(t_game *g)
{
	calc(g);
	key_update(g, g->map);
	// draw(g);
	return (0);
}
