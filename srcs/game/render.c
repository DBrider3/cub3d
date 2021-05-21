/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 06:00:36 by dcho              #+#    #+#             */
/*   Updated: 2021/05/21 21:24:39 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_color(t_game *g, int x, int color, int section)
{
	int		start;
	int		end;
	int		y;

	// 배경색 채우기
	if (section)
	{
		start = 0;
		end = g->height / 2;
	}
	else
	{
		start = g->height / 2;
		end = g->height;
	}
	y = start;
	while (y < end)
	{
		g->img.addr[y * g->img.size_l / 4 + x] = color;
		y++;
	}
}

void	game_display(t_game *g)
{
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, g->img.img);
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, g->win);
}

void	draw_texture(t_game *g, t_raycast *rc, int x)
{
	int		y;
	// draw_start 부터 라인 그리기 반복
	y = rc->draw_start - 1;
	while (++y < rc->draw_end)
	{
		// & 연산으로  높이보다 크지 않게 하는 overflow 방지 코드
		rc->tex_y = (int)rc->tex_pos & (TEX_HEIGHT - 1);
		// 다음 텍스쳐 정확한 y값 구해줌
		rc->tex_pos += rc->step;
		// 해당 텍스쳐 컬러 구해줌
		rc->color = g->texture[rc->tex_num][TEX_HEIGHT * rc->tex_y + rc->tex_x];
		// y면에 부딪히면 화면을 더 어둡게 해줌
		if (rc->side == 1)
			rc->color = (rc->color >> 1) & 8355711;
		// 이미지에 바로 넣어준다.
		g->img.addr[y * g->img.size_l / 4 + x] = rc->color;
	}
}

void	draw_sprite(t_game *g, t_sprite *s)
{
	int		y;

	while (s->draw_start_x < s->draw_end_x)
	{
		/*
		tex_x: 텍스쳐의 x 좌표
		256, 128을 곱하는게 오버플로우 방지
		draw_start_x - (-sprite_width / 2 + screen_x): 벽 한칸에서의 현재 광선의 위치
		* TEX_WIDTH / sprite_width: TEX_WIDTH 곱해야 텍스쳐상의 위치 변환 sprite_width
		로 나눠서 스프라이트 크기에 맞춰 값 가져옴.
		*/
		s->tex_x = (int)((256 * (s->draw_start_x - (-s->sprite_width / 2
					+ s->screen_x)) * TEX_WIDTH / s->sprite_width) / 256);
		// 스프라이트를 그려야하는 조건, 벽의 거리가 더 길어야 그린다.
		if (s->trans_y > 0 && s->trans_y < g->zbuf[s->draw_start_x]
			&& s->tex_x >= 0)
		{
			y = s->draw_start_y - 1;
			while (++y < s->draw_end_y)
			{
				// 스프라이트 텍스쳐에서 y가 얼만큼 가야하는지 구함
				s->d = (y - s->vm_screen) * 256 - g->height * 128
						+ s->sprite_height * 128;
				// 스프라이트 텍스쳐 y 비례해서 구해줌
				s->tex_y = ((s->d * TEX_HEIGHT) / s->sprite_height) / 256;
				// 컬러 소환
				s->color = g->texture[4][TEX_WIDTH * s->tex_y + s->tex_x];
				// 검정색 아닐때만 이미지에 저장
				if ((s->color & 0x00FFFFFF) != 0)
					g->img.addr[y * g->img.size_l / 4 \
					+ s->draw_start_x] = s->color;
			}
		}
		s->draw_start_x++;
	}
}
