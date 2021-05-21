/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 21:27:11 by dcho              #+#    #+#             */
/*   Updated: 2021/05/21 18:05:15 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotation(t_game *g, double degree)
{
	double		rad;
	double		olddirx;
	double		oldplanex;

	if (degree)
	{
		rad = M_PI * degree / 180;
		olddirx = g->dir_x;
		/*
		**  회전 행렬   [cos(rad) -sin(rad)] [x]
		**           [sin(rad)  cos(rad)] [y]
		*/
		g->dir_x = g->dir_x * cos(rad) - g->dir_y * sin(rad);
		g->dir_y = olddirx * sin(rad) + g->dir_y * cos(rad);
		oldplanex = g->plane_x;
		g->plane_x = g->plane_x * cos(rad) - g->plane_y * sin(rad);
		g->plane_y = oldplanex * sin(rad) + g->plane_y * cos(rad);
	}
}

void	game_main(t_game *g, t_options *op)
{
	// 각종 방향 초기화
	init_direction(g);
	// 텍스쳐, zbuf 할당
	init_texture(g);
	// loc, dist 할당
	init_sprite(g->sprite);
	// 파싱한 컬러값 저장
	g->f_color = create_trgb(op->f[0], op->f[1], op->f[2]);
	g->c_color = create_trgb(op->c[0], op->c[1], op->c[2]);
	// 초기 플레이어 방향에 맞춰 회전
	rotation(g, g->dir);
	// 파싱된 텍스쳐 로드
	load_texture(g, op);
}

// mlx_loop 가 돌면서 실행할 함수들
int		game_loop(t_game *g)
{
	// 그래픽
	graphic(g);
	// 키 업데이트
	key_update(g, g->map);
	return (0);
}
