/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_identifier_sub.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 02:01:48 by dcho              #+#    #+#             */
/*   Updated: 2021/05/21 09:48:29 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void			check_string(char *s)
{
	int		cnt;

	cnt = 0;
	while (*s)
	{
		if (*s == ' ')
			exit_error("not the correct parsing");
		if (!(ft_isdigit(*s)))
		{
			if (*s == ',')
				cnt++;
			else
				exit_error("not the correct parsing");
		}
		if (cnt > 2)
			exit_error("not the correct parsing");
		s++;
	}
}

static void			check_flag(char **comma, t_options *op, int flag)
{
	int		i;

	i = 0;
	if (flag == 1)
	{
		check_duplication_two(op, 7);
		while (i < 3)
		{
			op->f[i] = ft_atoi(comma[i]);
			if (op->f[i] < 0 || op->f[i] > 255)
				exit_error("not the correct parsing");
			i++;
		}
	}
	else if (flag == 2)
	{
		check_duplication_two(op, 8);
		while (i < 3)
		{
			op->c[i] = ft_atoi(comma[i]);
			if (op->c[i] < 0 || op->c[i] > 255)
				exit_error("not the correct parsing");
			i++;
		}
	}
}

static int			input_r_check(char **s)
{
	int		i;
	int		j;

	i = -1;
	while (++i < 2)
	{
		j = 0;
		while (*(s[i] + j))
		{
			if (!(ft_isdigit(*(s[i] + j))))
				return (ERROR);
			j++;
		}
	}
	return (NO_ERROR);
}

int					input_r(char **input, t_options *op)
{
	int		i;
	int		index;

	if (check_size(input) != 3)
		return (ERROR);
	check_duplication_one(op, 1);
	if (input_r_check(input + 1))
		return (ERROR);
	i = 1;
	index = 0;
	while (index < 2)
	{
		op->r[index] = ft_atoi(*(input + i));
		if (op->r[index] <= 0 || op->r[index] >= 2147483647)
			return (ERROR);
		index++;
		i++;
	}
	return (NO_ERROR);
}

int					input_fc(char **input, t_options *op, int flag)
{
	char	**comma;

	if (check_size(input) != 2)
		return (ERROR);
	check_string(input[1]);
	if (!(comma = ft_split(*(input + 1), ',')))
		return (ERROR);
	if (check_size(comma) != 3)
		return (ERROR);
	check_flag(comma, op, flag);
	return (free_inside(comma) + NO_ERROR);
}
