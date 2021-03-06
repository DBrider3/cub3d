/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 23:17:41 by dcho              #+#    #+#             */
/*   Updated: 2021/05/21 22:07:56 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int		key_press(int key, t_game *g)
{
	if (key == K_ESE)
		exit_btn();
	else if (key == K_W)
		g->key_w = 1;
	else if (key == K_A)
		g->key_a = 1;
	else if (key == K_S)
		g->key_s = 1;
	else if (key == K_D)
		g->key_d = 1;
	return (0);
}

int		key_release(int key, t_game *g)
{
	if (key == K_ESE)
		exit_btn();
	else if (key == K_W)
		g->key_w = 0;
	else if (key == K_A)
		g->key_a = 0;
	else if (key == K_S)
		g->key_s = 0;
	else if (key == K_D)
		g->key_d = 0;
	return (0);
}

void	key_update(t_game *g, t_map *m)
{
	if (g->key_w)
	{
		if (ft_strchr("0NESW", m->map[(int)(g->pos_x + g->dir_x * g->movespeed)]
		[(int)(g->pos_y)]) > 0)
			g->pos_x += g->dir_x * g->movespeed;
		if (ft_strchr(" 0NESW", m->map[(int)(g->pos_x)]
		[(int)(g->pos_y + g->dir_y * g->movespeed)]) > 0)
			g->pos_y += g->dir_y * g->movespeed;
	}
	if (g->key_s)
	{
		if (ft_strchr("0NESW", m->map[(int)(g->pos_x - g->dir_x * g->movespeed)]
		[(int)(g->pos_y)]))
			g->pos_x -= g->dir_x * g->movespeed;
		if (ft_strchr("0NESW", m->map[(int)(g->pos_x)]
		[(int)(g->pos_y - g->dir_y * g->movespeed)]))
			g->pos_y -= g->dir_y * g->movespeed;
	}
	if (g->key_d)
		rotation(g, -(g->rotspeed));
	if (g->key_a)
		rotation(g, (g->rotspeed));
}
