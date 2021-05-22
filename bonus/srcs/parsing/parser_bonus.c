/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 22:12:38 by dcho              #+#    #+#             */
/*   Updated: 2021/05/20 17:45:36 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

int				parse_main(char *f, t_options *op, t_game *g, t_sprite *s)
{
	char	*line;
	int		ret;
	int		flag;
	int		fd;

	if ((fd = open(f, O_RDONLY)) == -1)
	{
		printf("tes\n");
		return (ERROR);
	}
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
	g->map = op->map;
	map_check_main(op->map, g);
	return (NO_ERROR);
}
