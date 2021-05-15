/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 22:12:38 by dcho              #+#    #+#             */
/*   Updated: 2021/05/15 19:35:46 by dcho             ###   ########.fr       */
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

int				parse_main(char *s, t_options *op, t_game *g)
{
	char	*line;
	int		ret;
	int		flag;
	int		fd;

	if ((fd = open(s, O_RDONLY)) == -1)
		return (ERROR);
	init_start(op, g);
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
	g->posx = -1;
	g->posy = -1;
	map_check_main(op->map, g);
	g->map = op->map;
	return (NO_ERROR);
}
