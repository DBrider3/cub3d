/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 19:23:36 by dcho              #+#    #+#             */
/*   Updated: 2021/05/15 21:11:39 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_start(t_options *op, t_game *g)
{
	ft_bzero(g, sizeof(*g));
	ft_bzero(op, sizeof(*op));
	ft_memset(op->f, -1, sizeof(op->f));
	ft_memset(op->c, -1, sizeof(op->c));
}

void	init_direction(t_game *g)
{
	g->dirx = -1;
	g->diry = 0;
	g->planex = 0;
	g->planey = 0.66;
	g->movespeed = 0.05;
	g->rotspeed = 2;
}

void	game_init_allocation(t_game *g)
{
	int		i;

	if (!(g->texture = ft_calloc(5, sizeof(int*))))
		exit_error("malloc error");
	i = 0;
	while (i < 5)
	{
		if (!(g->texture[i++] = ft_calloc((texHeight * texWidth), sizeof(int))))
			exit_error("malloc error");
	}
}
