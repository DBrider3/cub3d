/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 01:20:18 by dcho              #+#    #+#             */
/*   Updated: 2021/05/12 15:31:45 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		check_duplication_one(t_options *op, int flag)
{
	if (flag == 1)
	{
		if ((op->flags & RFLAG) == RFLAG)
			exit_error("identifier duplication");
		op->flags = op->flags | RFLAG;
	}
	else if (flag == 2)
	{
		if ((op->flags & NOFLAG) == NOFLAG)
			exit_error("identifier duplication");
		op->flags = op->flags | NOFLAG;
	}
	else if (flag == 3)
	{
		if ((op->flags & SOFLAG) == SOFLAG)
			exit_error("identifier duplication");
		op->flags = op->flags | SOFLAG;
	}
	else if (flag == 4)
	{
		if ((op->flags & WEFLAG) == WEFLAG)
			exit_error("identifier duplication");
		op->flags = op->flags | WEFLAG;
	}
}

void		check_duplication_two(t_options *op, int flag)
{
	if (flag == 5)
	{
		if ((op->flags & EAFLAG) == EAFLAG)
			exit_error("identifier duplication");
		op->flags = op->flags | EAFLAG;
	}
	else if (flag == 6)
	{
		if ((op->flags & SFLAG) == SFLAG)
			exit_error("identifier duplication");
		op->flags = op->flags | SFLAG;
	}
	else if (flag == 7)
	{
		if ((op->flags & FFLAG) == FFLAG)
			exit_error("identifier duplication");
		op->flags = op->flags | FFLAG;
	}
	else if (flag == 8)
	{
		if ((op->flags & CFLAG) == CFLAG)
			exit_error("identifier duplication");
		op->flags = op->flags | CFLAG;
	}
}
