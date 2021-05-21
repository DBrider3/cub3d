/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_identifier_sub.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 02:01:48 by dcho              #+#    #+#             */
/*   Updated: 2021/05/21 12:52:22 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void			check_string(char *s)
{
	int		cnt;

	// ','개수 체크 cnt 초기화
	cnt = 0;
	while (*s)
	{
		// 빈칸이 하나라도 있으면 에러
		if (*s == ' ')
			exit_error("not the correct parsing");
		// 숫자가 아닐시
		if (!(ft_isdigit(*s)))
		{
			// ',' 개수 체크
			if (*s == ',')
				cnt++;
			// 숫자가 아닐때 에러
			else
				exit_error("not the correct parsing");
		}
		s++;
	}
	// 개수가 2개가 아니면
	if (cnt != 2)
		exit_error("not the correct parsing");
}

static void			check_flag(char **comma, t_options *op, int flag)
{
	int		i;

	i = 0;
	if (flag == 1)
	{
		// 비트 연산으로 기준 잡고 구분자가 중복인지 체크
		check_duplication_two(op, 7);
		while (i < 3)
		{
			// 배열에 숫자로 값 저장
			op->f[i] = ft_atoi(comma[i]);
			// rgb 유효성 체크
			if (op->f[i] < 0 || op->f[i] > 255)
				exit_error("not the correct parsing");
			i++;
		}
	}
	else if (flag == 2)
	{
		// 비트 연산으로 기준 잡고 구분자가 중복인지 체크
		check_duplication_two(op, 8);
		while (i < 3)
		{
			// 배열에 숫자로 값 저장
			op->c[i] = ft_atoi(comma[i]);
			// rgb 유효성 체크
			if (op->c[i] < 0 || op->c[i] > 255)
				exit_error("not the correct parsing");
			i++;
		}
	}
}

// r 인자들이 제대로 숫자만 들어있는지 체크
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

	// 총 사이즈 3개 맞는지 체크
	if (check_size(input) != 3)
		return (ERROR);
	// 비트 연산으로 기준 잡고 구분자가 중복인지 체크
	check_duplication_one(op, 1);
	// r 인자들이 제대로 숫자만 들어있는지 체크
	if (input_r_check(input + 1))
		return (ERROR);
	i = 1;
	index = 0;
	while (index < 2)
	{
		// 숫자로 변환후 값 넣어주기
		op->r[index] = ft_atoi(*(input + i));
		// 값 체크
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

	// 인자가 2개인지 체크
	if (check_size(input) != 2)
		return (ERROR);
	// f,c 파싱하기전에 문자열 체크
	check_string(input[1]);
	// ',' 기준 스플릿
	if (!(comma = ft_split(*(input + 1), ',')))
		return (ERROR);
	// 3 사이즈가 아니면 에러
	if (check_size(comma) != 3)
		return (ERROR);
	check_flag(comma, op, flag);
	return (free_inside(comma) + NO_ERROR);
}
