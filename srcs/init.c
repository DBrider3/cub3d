/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 19:23:36 by dcho              #+#    #+#             */
/*   Updated: 2021/05/19 20:52:04 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_start(t_options *op, t_game *g, t_sprite *s)
{
	ft_bzero(op, sizeof(*op));
	ft_bzero(g, sizeof(*g));
	ft_bzero(s, sizeof(*s));
	ft_memset(op->f, -1, sizeof(op->f));
	ft_memset(op->c, -1, sizeof(op->c));
	g->pos_x = -1;
	g->pos_y = -1;
	g->sprite = s;
}

void	init_direction(t_game *g)
{
	g->dir_x = -1;
	g->dir_y = 0;
	g->plane_x = 0;
	g->plane_y = 0.66;
	g->movespeed = 0.05;
	g->rotspeed = 2;
}

void	init_sprite(t_sprite *s)
{
	int		i;

	if (!(s->loc_sprite = ft_calloc(s->num, sizeof(double*))))
		exit_error("malloc error");
	i = 0;
	while (i < s->num)
	{
		if (!(s->loc_sprite[i++] = ft_calloc(2, sizeof(double))))
			exit_error("malloc error");
	}
	if (!(s->sprite_dist = ft_calloc(s->num, sizeof(double))))
		exit_error("malloc error");

}

void	init_texture(t_game *g)
{
	int		i;

	if (!(g->texture = ft_calloc(5, sizeof(int*))))
		exit_error("malloc error");
	i = 0;
	while (i < 5)
	{
		if (!(g->texture[i++] = ft_calloc((TEX_HEIGHT * TEX_WIDTH), sizeof(int))))
			exit_error("malloc error");
	}
	g->zbuf = malloc(g->width * sizeof(double));
}
