/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 22:12:38 by dcho              #+#    #+#             */
/*   Updated: 2021/05/18 06:10:30 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		parse_sub(t_options *op, char *line, int *flag)
{
	if (!(check_identifier(*op)))
	{
		if (parse_identifier(line, op))
			return (free_value(line) + ERROR);
	}
	else if (*flag == 0)
	{
		if (find_map(line, flag, op))
			return (free_value(line) + ERROR);
	}
	else
	{
		if (add_map_line(op->map, ft_strdup(line)))
			return (free_value(line) + ERROR);
	}
	free(line);
	return (NO_ERROR);
}

static void		distance_sprite(t_game *g, t_sprite *s)
{
	for (int i = 0; i < s->num; i++)
	{
		s->sprite_dist[i] = (g->pos_x - s->loc_sprite[i][0]) * (g->pos_x - s->loc_sprite[i][0])
							+ (g->pos_y - s->loc_sprite[i][1]) * (g->pos_y - s->loc_sprite[i][1]);
	}
}

static void		sort_sprite(t_game *g, t_sprite *s)
{
	double	x, y;
	double	sprite_dist_tmp;

	// distance_sprite(g, s);
	for (int i = 0; i < s->num; i++)
	{
		for (int j = 0; j < s->num - 1; j++)
		{
			if (s->sprite_dist[j] > s->sprite_dist[j + 1])
			{
				x = s->loc_sprite[j][0];
				y = s->loc_sprite[j][1];
				s->loc_sprite[j][0] = s->loc_sprite[j + 1][0];
				s->loc_sprite[j][1] = s->loc_sprite[j + 1][1];
				s->loc_sprite[j + 1][0] = x;
				s->loc_sprite[j + 1][1] = y;
				sprite_dist_tmp = s->sprite_dist[j];
				s->sprite_dist[j] = s->sprite_dist[j + 1];
				s->sprite_dist[j + 1] = sprite_dist_tmp;
			}
		}
	}
}

static void		make_sprite_array(t_game *g, t_sprite *s)
{
	int		x;
	int		y;
	int		index;

	init_sprite(s);
	x = -1;
	index = 0;
	while (++x < g->map->index)
	{
		y = 0;
		while (g->map->map[x][y] != 0)
		{
			if (g->map->map[x][y] == '2')
			{
				s->loc_sprite[index][0] = 1.0 * x + 0.4999;
				s->loc_sprite[index][1] = 1.0 * y + 0.4999;
				if (index++ >= s->num)
					exit_error("map search error");
			}
			y++;
		}
	}
	distance_sprite(g, s);
	sort_sprite(g, s);
	for (int i = 0; i < s->num; i++)
	{
		printf("[%lf] [%lf] [%lf]\n", s->loc_sprite[i][0], s->loc_sprite[i][1], s->sprite_dist[i]);
	}
}

int				parse_main(char *f, t_options *op, t_game *g, t_sprite *s)
{
	char	*line;
	int		ret;
	int		flag;
	int		fd;

	if ((fd = open(f, O_RDONLY)) == -1)
		return (ERROR);
	init_start(op, g, s);
	if (new_map(&op->map))
		return (ERROR);
	flag = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (parse_sub(op, line, &flag))
			return (ERROR);
	}
	free(line);
	close(fd);
	g->pos_x = -1;
	g->pos_y = -1;
	map_check_main(op->map, g, s);
	g->map = op->map;
	make_sprite_array(g, s);
	g->sprite = s;
	return (NO_ERROR);
}
