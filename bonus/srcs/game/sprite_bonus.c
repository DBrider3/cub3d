/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 05:52:52 by dcho              #+#    #+#             */
/*   Updated: 2021/05/21 22:20:23 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void		make_sprite_array(t_game *g, t_sprite *s)
{
	int		x;
	int		y;
	int		index;

	x = -1;
	index = 0;
	while (++x < g->map->index)
	{
		y = 0;
		while (g->map->map[x][y] != 0)
		{
			if (g->map->map[x][y] == '2' || g->map->map[x][y] == '3')
			{
				s->tex_num[index] = g->map->map[x][y] == '2' ? 4 : 5;
				s->loc_sprite[index][0] = 1.0 * x + 0.4999;
				s->loc_sprite[index][1] = 1.0 * y + 0.4999;
				if (index++ >= s->num)
					exit_error("map search error");
			}
			y++;
		}
	}
	sort_sprite(g, s);
}

static void		calc_sprite(t_game *g, t_sprite *s, int i)
{
	s->sprite_x = s->loc_sprite[i][0] - g->pos_x;
	s->sprite_y = s->loc_sprite[i][1] - g->pos_y;
	s->invdet = 1.0 / (g->plane_x * g->dir_y - g->dir_x * g->plane_y);
	s->trans_x = s->invdet * \
				(g->dir_y * s->sprite_x - g->dir_x * s->sprite_y);
	s->trans_y = s->invdet *
				(-g->plane_y * s->sprite_x + g->plane_x * s->sprite_y);
	s->screen_x = (int)(g->width / 2) * (1 + s->trans_x / s->trans_y);
	s->vm_screen = (int)(V_MOVE / s->trans_y);
	s->sprite_height = (int)fabs((g->height / s->trans_y) / V_DIV);
	s->draw_start_y = -s->sprite_height / 2 + g->height / 2 + s->vm_screen;
	if (s->draw_start_y < 0)
		s->draw_start_y = 0;
	s->draw_end_y = s->sprite_height / 2 + g->height / 2 + s->vm_screen;
	if (s->draw_end_y >= g->height)
		s->draw_end_y = g->height;
	s->sprite_width = (int)fabs((g->height / s->trans_y) / U_DIV);
	s->draw_start_x = -s->sprite_width / 2 + s->screen_x;
	if (s->draw_start_x < 0)
		s->draw_start_x = 0;
	s->draw_end_x = s->sprite_width / 2 + s->screen_x;
	if (s->draw_end_x >= g->width)
		s->draw_end_x = g->width;
}

void			sprite_main(t_game *g, t_sprite *s)
{
	int		i;

	make_sprite_array(g, s);
	i = -1;
	while (++i < s->num)
	{
		calc_sprite(g, s, i);
		draw_sprite(g, s, i);
	}
}
