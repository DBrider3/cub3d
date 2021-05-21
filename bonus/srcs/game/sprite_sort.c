/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 22:10:20 by dcho              #+#    #+#             */
/*   Updated: 2021/05/21 22:20:31 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void		sort_texture_num(t_sprite *s, int index)
{
	int		tmp;

	tmp = s->tex_num[index];
	s->tex_num[index] = s->tex_num[index + 1];
	s->tex_num[index + 1] = tmp;
}

static void		sort_dist(t_sprite *s, int index)
{
	double	tmp;

	tmp = s->sprite_dist[index];
	s->sprite_dist[index] = s->sprite_dist[index + 1];
	s->sprite_dist[index + 1] = tmp;
}

static void		distance_sprite(t_game *g, t_sprite *s)
{
	int		i;

	i = -1;
	while (++i < s->num)
	{
		s->sprite_dist[i] = (g->pos_x - s->loc_sprite[i][0]) *
							(g->pos_x - s->loc_sprite[i][0])
							+ (g->pos_y - s->loc_sprite[i][1]) *
							(g->pos_y - s->loc_sprite[i][1]);
	}
}

void			sort_sprite(t_game *g, t_sprite *s)
{
	int		index[2];
	double	loc_sprite_tmp[2];

	distance_sprite(g, s);
	index[0] = -1;
	while (++index[0] < s->num)
	{
		index[1] = -1;
		while (++index[1] < s->num - 1)
		{
			if (s->sprite_dist[index[1]] < s->sprite_dist[index[1] + 1])
			{
				loc_sprite_tmp[0] = s->loc_sprite[index[1]][0];
				loc_sprite_tmp[1] = s->loc_sprite[index[1]][1];
				s->loc_sprite[index[1]][0] = s->loc_sprite[index[1] + 1][0];
				s->loc_sprite[index[1]][1] = s->loc_sprite[index[1] + 1][1];
				s->loc_sprite[index[1] + 1][0] = loc_sprite_tmp[0];
				s->loc_sprite[index[1] + 1][1] = loc_sprite_tmp[1];
				sort_dist(s, index[1]);
				sort_texture_num(s, index[1]);
			}
		}
	}
}
