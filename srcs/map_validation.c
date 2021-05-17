/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:06:16 by dcho              #+#    #+#             */
/*   Updated: 2021/05/16 16:17:38 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		map_check_basic(char c)
{
	if (ft_strchr(FULLFLAG, c) == 0)
		return (ERROR);
	return (NO_ERROR);
}

static int		map_check_validation(t_map *m, int i, int j)
{
	int		x;

	if ((int)ft_strlen(m->map[i + 1]) <= j
	|| (int)ft_strlen(m->map[i - 1]) <= j)
		return (ERROR);
	x = ft_strlen(m->map[i]) - 1;
	if (j >= x || j < 1 || i >= m->index - 1
	|| i < 1)
		return (ERROR);
	if (ft_strchr(MAPFLAG, m->map[i - 1][j]) == 0 ||
	ft_strchr(MAPFLAG, m->map[i + 1][j]) == 0 ||
	ft_strchr(MAPFLAG, m->map[i][j - 1]) == 0 ||
	ft_strchr(MAPFLAG, m->map[i][j + 1]) == 0)
		return (ERROR);
	return (NO_ERROR);
}

static void		position_check(char c, t_game *g, int i, int j)
{
	if (ft_strchr(POS, c))
	{
		if (g->pos_x == -1 || g->pos_y == -1)
		{
			g->pos_x = i;
			g->pos_y = j;
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

void			map_check_main(t_map *m, t_game *g)
{
	int		i;
	int		j;

	i = 0;
	while (i < m->index)
	{
		j = 0;
		if (ft_strlen(m->map[i]) == 0)
			exit_error("map error");
		while (m->map[i][j] != 0)
		{
			if (map_check_basic(m->map[i][j]))
				exit_error("map error");
			if (m->map[i][j] != '1' && m->map[i][j] != ' ')
			{
				if (map_check_validation(m, i, j))
					exit_error("map error");
				position_check(m->map[i][j], g, i, j);
			}
			j++;
		}
		i++;
	}
	if (g->pos_x == -1 || g->pos_y == -1)
		exit_error("no player exists");
}
