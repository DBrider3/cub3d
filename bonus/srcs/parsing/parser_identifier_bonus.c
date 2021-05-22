/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_identifier.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 16:27:52 by dcho              #+#    #+#             */
/*   Updated: 2021/05/21 09:48:01 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int			separate_identifier(t_options *op, char **input)
{
	int		res;

	if (ft_strncmp(input[0], "R\0", 2) == 0)
		res = input_r(input, op);
	else if (ft_strncmp(input[0], "NO\0", 3) == 0)
		res = input_file_one(input, op, 1);
	else if (ft_strncmp(input[0], "SO\0", 3) == 0)
		res = input_file_one(input, op, 2);
	else if (ft_strncmp(input[0], "WE\0", 3) == 0)
		res = input_file_two(input, op, 3);
	else if (ft_strncmp(input[0], "EA\0", 3) == 0)
		res = input_file_two(input, op, 4);
	else if (ft_strncmp(input[0], "S\0", 2) == 0)
		res = input_file_two(input, op, 5);
	else if (ft_strncmp(input[0], "F\0", 2) == 0)
		res = input_fc(input, op, 1);
	else if (ft_strncmp(input[0], "C\0", 2) == 0)
		res = input_fc(input, op, 2);
	else
		res = ERROR;
	return (res);
}

static void			input_file_check(char *s)
{
	int		fd;

	if ((fd = open(s, O_RDONLY)) == -1)
		exit_error("not the correct parsing");
}

int					input_file_one(char **input, t_options *op, int flag)
{
	if (check_size(input) != 2)
		return (ERROR);
	input_file_check(*(input + 1));
	if (flag == 1)
	{
		check_duplication_one(op, 2);
		op->no = ft_strdup(*(input + 1));
	}
	else if (flag == 2)
	{
		check_duplication_one(op, 3);
		op->so = ft_strdup(*(input + 1));
	}
	return (NO_ERROR);
}

int					input_file_two(char **input, t_options *op, int flag)
{
	if (check_size(input) != 2)
		return (ERROR);
	input_file_check(*(input + 1));
	if (flag == 3)
	{
		check_duplication_one(op, 4);
		op->we = ft_strdup(*(input + 1));
	}
	else if (flag == 4)
	{
		check_duplication_two(op, 5);
		op->ea = ft_strdup(*(input + 1));
	}
	else if (flag == 5)
	{
		check_duplication_two(op, 6);
		op->s = ft_strdup(*(input + 1));
	}
	return (NO_ERROR);
}

int					parse_identifier(char *line, t_options *op)
{
	char	**input;
	int		res;

	input = ft_split(line, ' ');
	if (input[0] == 0)
		return (free_inside(input) + NO_ERROR);
	res = separate_identifier(op, input);
	return (free_inside(input) + res);
}
