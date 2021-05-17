/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 22:35:39 by dcho              #+#    #+#             */
/*   Updated: 2021/05/12 03:27:53 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				new_map(t_map **m)
{
	if (!(*m = malloc(sizeof(t_map))))
		return (ERROR);
	if (!((*m)->map = malloc(sizeof(char*) * INITAIL_SIZE)))
		return (ERROR);
	(*m)->index = 0;
	(*m)->size = INITAIL_SIZE;
	(*m)->max_col = 0;
	return (NO_ERROR);
}

static int		expand_map(t_map *m)
{
	char	**map;
	int		i;

	map = m->map;
	m->size *= 2;
	if (!(m->map = malloc(sizeof(char*) * m->size)))
	{
		free(map);
		return (ERROR);
	}
	i = 0;
	while (i < m->index)
	{
		m->map[i] = map[i];
		i++;
	}
	free(map);
	return (NO_ERROR);
}

int				add_map_line(t_map *m, char *line)
{
	int		len;

	if (m->index == m->size && expand_map(m))
		return (ERROR);
	len = ft_strlen(line);
	if (m->max_col < len)
		m->max_col = len;
	m->map[m->index] = line;
	m->index++;
	return (NO_ERROR);
}

void			del_map(t_map *m)
{
	int		i;

	i = 0;
	while (i < m->index)
		free(m->map[i++]);
	free(m->map);
	free(m);
}

int				find_map(char *line, int *flag, t_options *op)
{
	int		i;

	i = 0;
	while (*(line + i))
	{
		if (*(line + i) == '1')
		{
			if (add_map_line(op->map, ft_strdup(line)))
				return (ERROR);
			*flag = 1;
			break ;
		}
		else if (*(line + i) == ' ');
		else
			exit_error("not the correct parsing");
		i++;
	}
	return (NO_ERROR);
}
