/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:06:16 by dcho              #+#    #+#             */
/*   Updated: 2021/05/20 17:54:53 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int		map_check_basic(char c)
{
	if (ft_strchr(FULLFLAG, c) == 0)
		return (ERROR);
	return (NO_ERROR);
}

static int		map_check_validation(t_map *m, int i, int j)
{
	if (j >= (int)ft_strlen(m->map[i]) - 1 || j < 1
	|| i >= m->index - 1 || i < 1)
		return (ERROR);
	if ((int)ft_strlen(m->map[i + 1]) <= j
	|| (int)ft_strlen(m->map[i - 1]) <= j)
		return (ERROR);
	if (m->map[i - 1][j] == ' ' || m->map[i + 1][j] == ' ' ||
	m->map[i][j - 1] == ' ' || m->map[i][j + 1] == ' ')
		return (ERROR);
	return (NO_ERROR);
}

static void		position_check(char c, t_game *g, int x, int y)
{
	if (ft_strchr(POS, c))
	{
		if (g->pos_x == -1 || g->pos_y == -1)
		{
			g->pos_x = x;
			g->pos_y = y;
			if (c == 'N')
				g->dir = 0;
			else if (c == 'W')
				g->dir = 90;
			else if (c == 'S')
				g->dir = 180;
			else if (c == 'E')
				g->dir = 270;
		}
		else
			exit_error("player already exists");
	}
}

static void		sprite_check(char c, t_sprite *s)
{
	if (c == '2' || c== '3')
		s->num++;
}

void			map_check_main(t_map *m, t_game *g)
{
	int		x;
	int		y;

	x = -1;
	while (++x < m->index)
	{
		y = 0;
		if (m->map[x][y] == '\0')
			exit_error("map error");
		while (m->map[x][y] != 0)
		{
			if (map_check_basic(m->map[x][y]))
				exit_error("map error");
			if (m->map[x][y] != '1' && m->map[x][y] != ' ')
			{
				if (map_check_validation(m, x, y))
					exit_error("map error");
				position_check(m->map[x][y], g, x, y);
				sprite_check(m->map[x][y], g->sprite);
			}
			y++;
		}
	}
	if (g->pos_x == -1 || g->pos_y == -1)
		exit_error("no player exists");
}
