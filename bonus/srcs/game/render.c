/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 06:00:36 by dcho              #+#    #+#             */
/*   Updated: 2021/05/20 18:09:18 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_color(t_game *g, int x, int color, int section)
{
	int		start;
	int		end;
	int		y;

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

	y = rc->draw_start - 1;
	while (++y < rc->draw_end)
	{
		rc->tex_y = (int)rc->tex_pos & (TEX_HEIGHT - 1);
		rc->tex_pos += rc->step;
		rc->color = g->texture[rc->tex_num][TEX_HEIGHT * rc->tex_y + rc->tex_x];
		if (rc->side == 1)
			rc->color = (rc->color >> 1) & 8355711;
		g->img.addr[y * g->img.size_l / 4 + x] = rc->color;
	}
}

void	draw_sprite(t_game *g, t_sprite *s, int index)
{
	int		y;

	while (s->draw_start_x < s->draw_end_x)
	{
		s->tex_x = (int)((256 * (s->draw_start_x - (-s->sprite_width / 2
					+ s->screen_x)) * TEX_WIDTH / s->sprite_width) / 256);
		if (s->trans_y > 0 && s->trans_y < g->zbuf[s->draw_start_x]
			&& s->tex_x >= 0)
		{
			y = s->draw_start_y - 1;
			while (++y < s->draw_end_y)
			{
				s->d = (y - s->vm_screen) * 256 - g->height * 128
						+ s->sprite_height * 128;
				s->tex_y = ((s->d * TEX_HEIGHT) / s->sprite_height) / 256;
				s->color = g->texture[s->tex_num[index]][TEX_WIDTH * s->tex_y + s->tex_x];
				if ((s->color & 0x00FFFFFF) != 0)
					g->img.addr[y * g->img.size_l / 4 \
					+ s->draw_start_x] = s->color;
			}
		}
		s->draw_start_x++;
	}
}
