/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 05:52:52 by dcho              #+#    #+#             */
/*   Updated: 2021/05/21 21:07:27 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		distance_sprite(t_game *g, t_sprite *s)
{
	int		i;

	i = -1;
	//
	while (++i < s->num)
	{ // 정렬을 위해 벡터 거리 구해준다.
	  // 제곱근 제외해줌 실제로 그릴때는 zbuf에 넣어둔 수직거리를 이용할 예정
		s->sprite_dist[i] = (g->pos_x - s->loc_sprite[i][0]) *
							(g->pos_x - s->loc_sprite[i][0])
							+ (g->pos_y - s->loc_sprite[i][1]) *
							(g->pos_y - s->loc_sprite[i][1]);
	}
}

static void		sort_sprite(t_game *g, t_sprite *s)
{
	int		index[2];
	double	loc_sprite_tmp[2];
	double	sprite_dist_tmp;

	// 거리 구해주는 함수 호출
	distance_sprite(g, s);
	// norm 땜에 억지로 끼워둔 배열 index[0] = i, index[1] = j 로 !
	index[0] = -1;
	while (++index[0] < s->num)
	{
		index[1] = -1;
		while (++index[1] < s->num - 1)
		{// 버블 소트로 각종 스프라이트 변수들 내림차순 정렬, 거리가 먼것부터 그려야 해서
			if (s->sprite_dist[index[1]] < s->sprite_dist[index[1] + 1])
			{
				loc_sprite_tmp[0] = s->loc_sprite[index[1]][0];
				loc_sprite_tmp[1] = s->loc_sprite[index[1]][1];
				s->loc_sprite[index[1]][0] = s->loc_sprite[index[1] + 1][0];
				s->loc_sprite[index[1]][1] = s->loc_sprite[index[1] + 1][1];
				s->loc_sprite[index[1] + 1][0] = loc_sprite_tmp[0];
				s->loc_sprite[index[1] + 1][1] = loc_sprite_tmp[1];
				sprite_dist_tmp = s->sprite_dist[index[1]];
				s->sprite_dist[index[1]] = s->sprite_dist[index[1] + 1];
				s->sprite_dist[index[1] + 1] = sprite_dist_tmp;
			}
		}
	}
}

static void		make_sprite_array(t_game *g, t_sprite *s)
{
	int		x;
	int		y;
	int		index;

	x = -1;
	index = 0;
	// 맵 돌면서 스프라이트 위치 구함.
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
	// 내림차순으로 정렬하기
	sort_sprite(g, s);
}

static void		calc_sprite(t_game *g, t_sprite *s, int i)
{
	// 스프라이트와 플레이어 위치를 빼서 스프라이트와 플레이어 사이의 거리를 구함
	s->sprite_x = s->loc_sprite[i][0] - g->pos_x;
	s->sprite_y = s->loc_sprite[i][1] - g->pos_y;
	// 역행렬에서  1 / ad-bc 부분
	s->invdet = 1.0 / (g->plane_x * g->dir_y - g->dir_x * g->plane_y);
	// 카메라 매트릭스 (카메라평면 +플레이어방향)의 역행렬과 스프라이트 행렬을 곱해줌
	s->trans_x = s->invdet * \
				(g->dir_y * s->sprite_x - g->dir_x * s->sprite_y);
	s->trans_y = s->invdet *
				(-g->plane_y * s->sprite_x + g->plane_x * s->sprite_y);
	// 스프라이트의 시작위치를 결정함 y가 클수록 멀어짐 깊이라고 생각하면됨
	s->screen_x = (int)(g->width / 2) * (1 + s->trans_x / s->trans_y);
	// vm_screen은 스프라이트를 스크린 아래로 내리기 위한 변수, 커질수록 밑으로 내려감
	s->vm_screen = (int)(V_MOVE / s->trans_y);
	// 스프라이트 높이 구하기
	s->sprite_height = (int)fabs((g->height / s->trans_y) / V_DIV);
	// 스프라이트 아래위 시작 끝 잡아주는 부분
	s->draw_start_y = -s->sprite_height / 2 + g->height / 2 + s->vm_screen;
	if (s->draw_start_y < 0)
		s->draw_start_y = 0;
	s->draw_end_y = s->sprite_height / 2 + g->height / 2 + s->vm_screen;
	if (s->draw_end_y >= g->height)
		s->draw_end_y = g->height;
	// 스프라이트 너비 구하기
	s->sprite_width = (int)fabs((g->height / s->trans_y) / U_DIV);
	// 스프라이트 좌우 시작 끝 잡아주는 부분
	s->draw_start_x = -s->sprite_width / 2 + s->screen_x;
	if (s->draw_start_x < 0)
		s->draw_start_x = 0;
	s->draw_end_x = s->sprite_width / 2 + s->screen_x;
	if (s->draw_end_x >= g->width)
		s->draw_end_x = g->width;
}

void			sprite_main(t_game *g, t_sprite *s)
{
	int		i;

	// 스프라이트 관련 배열을 만들고 정렬해 주는 함수 호출
	make_sprite_array(g, s);
	i = -1;
	while (++i < s->num)
	{
		calc_sprite(g, s, i);
		draw_sprite(g, s);
	}
}
