/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 01:20:18 by dcho              #+#    #+#             */
/*   Updated: 2021/05/21 12:02:11 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 비트 연산으로 기준 잡고 구분자가 중복인지 체크
void		check_duplication_one(t_options *op, int flag)
{
	// R 식별자 체크 2의 0승 의 자리로 and 연산
	if (flag == 1)
	{
		if ((op->flags & RFLAG) == RFLAG)
			exit_error("identifier duplication");
		op->flags = op->flags | RFLAG;
	}
	// NO 식별자 체크 2의 1승 의 자리로 and 연산
	else if (flag == 2)
	{
		if ((op->flags & NOFLAG) == NOFLAG)
			exit_error("identifier duplication");
		op->flags = op->flags | NOFLAG;
	}
	// SO 식별자 체크 2의 2승 의 자리로 and 연산
	else if (flag == 3)
	{
		if ((op->flags & SOFLAG) == SOFLAG)
			exit_error("identifier duplication");
		op->flags = op->flags | SOFLAG;
	}
	// WE 식별자 체크 2의 3승 의 자리로 and 연산
	else if (flag == 4)
	{
		if ((op->flags & WEFLAG) == WEFLAG)
			exit_error("identifier duplication");
		op->flags = op->flags | WEFLAG;
	}
}

void		check_duplication_two(t_options *op, int flag)
{
	// EA 식별자 체크 2의 4승 의 자리로 and 연산
	if (flag == 5)
	{
		if ((op->flags & EAFLAG) == EAFLAG)
			exit_error("identifier duplication");
		op->flags = op->flags | EAFLAG;
	}
	// S 식별자 체크 2의 5승 의 자리로 and 연산
	else if (flag == 6)
	{
		if ((op->flags & SFLAG) == SFLAG)
			exit_error("identifier duplication");
		op->flags = op->flags | SFLAG;
	}
	// F 식별자 체크 2의 6승 의 자리로 and 연산
	else if (flag == 7)
	{
		if ((op->flags & FFLAG) == FFLAG)
			exit_error("identifier duplication");
		op->flags = op->flags | FFLAG;
	}
	// C 식별자 체크 2의 7승 의 자리로 and 연산
	else if (flag == 8)
	{
		if ((op->flags & CFLAG) == CFLAG)
			exit_error("identifier duplication");
		op->flags = op->flags | CFLAG;
	}
}
