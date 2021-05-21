/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 06:13:54 by dcho              #+#    #+#             */
/*   Updated: 2021/05/21 20:33:06 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_raycasing(t_game *g, t_raycast *rc, int x)
{
	// 카메라 x는 카메라 평면상에 있을 때 x 좌표, 배수
	rc->camera_x = 2 * x / (double)g->width - 1;
	// 광선 방향 = 방향벡터 + 카메라 평면 * 배수(시야)
	rc->raydir_x = g->dir_x + g->plane_x * rc->camera_x;
	rc->raydir_y = g->dir_y + g->plane_y * rc->camera_x;
	// 플레이어의 맵에서의 위치
	rc->map_x = (int)g->pos_x;
	rc->map_y = (int)g->pos_y;
	// deltaDist 벡터는 공식으로 구함. 일정한 비율이기 때문에 한칸의 1로 함.
	rc->dd_x = fabs(1 / rc->raydir_x);
	rc->dd_y = fabs(1 / rc->raydir_y);
	// 광선 벡터의 방항을 알려주는 step
	rc->step_x = rc->raydir_x < 0 ? -1 : 1;
	rc->step_y = rc->raydir_y < 0 ? -1 : 1;
	// sideDist 벡터 초기값 셋팅, 비례로 곱해서 구함
	rc->sd_x = rc->raydir_x < 0 ? (g->pos_x - rc->map_x) * rc->dd_x : \
									(rc->map_x + 1.0 - g->pos_x) * rc->dd_x;
	rc->sd_y = rc->raydir_y < 0 ? (g->pos_y - rc->map_y) * rc->dd_y : \
									(rc->map_y + 1.0 - g->pos_y) * rc->dd_y;
}

static void	calc_dda(t_game *g, t_raycast *rc)
{
	int		hit;

	hit = 0;
	/* DDA 알고리즘
	sideDist 벡터를 누적으로 이용, x,y 비교해서 더 짧은 것에 더하면서
	step 증가와 side[0 -> x면(측), 1 -> y면(측)] 체크하고 그게 벽에 닿으면 종료
	*/
	while (hit == 0)
	{
		if (rc->sd_x < rc->sd_y)
		{
			rc->sd_x += rc->dd_x;
			rc->map_x += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->sd_y += rc->dd_y;
			rc->map_y += rc->step_y;
			rc->side = 1;
		}
		if (g->map->map[rc->map_x][rc->map_y] == '1')
			hit = 1;
	}
}

static void	calc_texture(t_game *g, t_raycast *rc)
{
	/*
	[x, y면에 따라 셋팅]
		- pwd(perpWallDist, 수직거리): 광선이 x,y 방향으로 얼마나 지나갔는지 나타냄
			비례식을 이용하여 연립방정식으로 관계식 세움
		- tex_num: 벽의 동서남북 구분
		- wall_x: 벽의 int형 좌표가 아닌 double형 좌표로 벽의 정확히 어디에 부딪혔는지 알려줌
	*/
	if (rc->side == 0)
	{
		rc->pwd = (rc->map_x - g->pos_x + (1 - rc->step_x) / 2) / rc->raydir_x;
		rc->tex_num = rc->step_x > 0 ? 1 : 0;
		rc->wall_x = g->pos_y + rc->pwd * rc->raydir_y;
	}
	else
	{
		rc->pwd = (rc->map_y - g->pos_y + (1 - rc->step_y) / 2) / rc->raydir_y;
		rc->tex_num = rc->step_y > 0 ? 3 : 2;
		rc->wall_x = g->pos_x + rc->pwd * rc->raydir_x;
	}
	// 높이를 수직거리로 나눠서 그려야 할 라인 높이 측정
	rc->l_height = rc->pwd == 0 ? 0 : (int)(g->height / rc->pwd);
	/*
	draw_start는높이, 라인 높이를 반 짤라 빼주는 방식
	draw_end는 더하는 방식, 범위를 벗어나면 처리 해줌.
	*/
	rc->draw_start = g->height / 2 - rc->l_height / 2;
	rc->draw_end = g->height / 2 + rc->l_height / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	if (rc->draw_end >= g->height)
		rc->draw_end = g->height - 1;
	// 내림함수를 써서 wall_x 자기자신을 빼고 텍스트 너비를 통해 텍스쳐 x 좌표 구함
	rc->tex_x = (int)((rc->wall_x - floor(rc->wall_x)) * (double)TEX_WIDTH);
	// 남, 서 방향은 좌우반대로 출력되기에 따로 처리 해준다.
	if (rc->tex_num == 1 || rc->tex_num == 2)
		rc->tex_x = TEX_WIDTH - rc->tex_x - 1;
	// 스크린에서의 벽의 한칸이 텍스쳐에서의 얼마만큼 갈건지 구해준다. (비례 구함)
	rc->step = 1.0 * TEX_HEIGHT / rc->l_height;
	/*
	처음 텍스쳐의 위치를 정하고 스텝을 곱해준다.
	0이 아니라 왜 식을 넣을까? l_height가 더 크면(벽에 가까이 다가가면) 그 만큼 계산해서
	텍스쳐의 컬러로 넣어줘야함.
	*/
	rc->tex_pos = (rc->draw_start - g->height / 2 + rc->l_height / 2)
					* rc->step;
}

void		raycasting_main(t_game *g)
{
	t_raycast	rc;
	int			x;

	x = -1;
	// 너비로 반복
	while (++x < g->width)
	{
		calc_raycasing(g, &rc, x);
		calc_dda(g, &rc);
		draw_color(g, x, g->c_color, 1);
		draw_color(g, x, g->f_color, 0);
		calc_texture(g, &rc);
		draw_texture(g, &rc, x);
		// zbuf에 각각 라인마다 직선거리를 넣어준다.
		g->zbuf[x] = rc.pwd;
	}
}
