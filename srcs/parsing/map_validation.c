/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 17:06:16 by dcho              #+#    #+#             */
/*   Updated: 2021/05/21 13:32:53 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 맵에 필수요소만 들어있는지 체크
static int		map_check_basic(char c)
{
	// " 012EWSN" 가 아니면 에러
	if (ft_strchr(FULLFLAG, c) == 0)
		return (ERROR);
	return (NO_ERROR);
}

// 맵 유효성 검사
static int		map_check_validation(t_map *m, int i, int j)
{
	// 현재 기준 동서남북 인덱스가 존재하지 않으면 에러
	if (j >= (int)ft_strlen(m->map[i]) - 1 || j < 1
	|| i >= m->index - 1 || i < 1)
		return (ERROR);
	// 한쪽 라인이 북,남 보다 길때 인덱스를 참고를 못하니까 에러
	if ((int)ft_strlen(m->map[i + 1]) <= j
	|| (int)ft_strlen(m->map[i - 1]) <= j)
		return (ERROR);
	// 맵 안에 빈칸 에러
	if (m->map[i - 1][j] == ' ' || m->map[i + 1][j] == ' ' ||
	m->map[i][j - 1] == ' ' || m->map[i][j + 1] == ' ')
		return (ERROR);
	return (NO_ERROR);
}

// 플레이어 체크
static void		position_check(char c, t_game *g, int x, int y)
{
	if (ft_strchr(POS, c))
	{
		// 플레이어 초기값일때만 넣기
		if (g->pos_x == -1 || g->pos_y == -1)
		{
			g->pos_x = x;
			g->pos_y = y;
			// 동서남북 체크는 각도로
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

// 스프라이트 개수 체크
static void		sprite_check(char c, t_sprite *s)
{
	if (c == '2')
		s->num++;
}

void			map_check_main(t_map *m, t_game *g)
{
	int		x;
	int		y;

	x = -1;
	while (++x < m->index)
	{
		y = 0;
		// 맵에 빈줄 있으면 에러처리
		if (m->map[x][y] == '\0')
			exit_error("map error");
		while (m->map[x][y] != 0)
		{
			// 맵에 필수요소만 들어있는지 체크
			if (map_check_basic(m->map[x][y]))
				exit_error("map error");
			// 플레이어, 빈공간, 스프라이트 체크
			if (m->map[x][y] != '1' && m->map[x][y] != ' ')
			{
				// 맵 유효성 체크
				if (map_check_validation(m, x, y))
					exit_error("map error");
				// 플레이어 체크
				position_check(m->map[x][y], g, x, y);
				// 스프라이트 개수 체크
				sprite_check(m->map[x][y], g->sprite);
			}
			y++;
		}
	}
	// 플레이어가 없다면 에러
	if (g->pos_x == -1 || g->pos_y == -1)
		exit_error("no player exists");
}
