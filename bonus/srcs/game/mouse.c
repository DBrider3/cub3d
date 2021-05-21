/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 10:21:40 by dcho              #+#    #+#             */
/*   Updated: 2021/05/21 22:22:16 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int		mouse_move(int x, int y, t_game *g)
{
	int speed;

	if (x < g->width && y < g->height)
	{
		if (x < g->mouse_old_x)
		{
			speed = (g->mouse_old_x - x) / 2;
			rotation(g, speed);
			g->mouse_old_x = x;
		}
		else
		{
			speed = (x - g->mouse_old_x) / 2;
			rotation(g, -speed);
			g->mouse_old_x = x;
		}
	}
	return (0);
}
