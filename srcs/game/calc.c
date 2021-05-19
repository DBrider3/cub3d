/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:47:56 by dcho              #+#    #+#             */
/*   Updated: 2021/05/20 00:54:05 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	verLine(t_game *g, int x, int start, int end, int color)
{
	int	y;

	y = start;
	while (y < end)
	{
		g->img.addr[y * g->img.size_l / 4 + x] = color;
		y++;
	}
}

static void	game_display(t_game *g)
{
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, g->img.img);
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, g->win);
}

static void calc_beginning(t_game *g, t_raycast *rc, int x)
{
	rc->camera_x = 2 * x / (double)g->width - 1;
	rc->raydir_x = g->dir_x + g->plane_x * rc->camera_x;
	rc->raydir_y = g->dir_y + g->plane_y * rc->camera_x;
	rc->map_x = (int)g->pos_x;
	rc->map_y = (int)g->pos_y;
	rc->dd_x = fabs(1 / rc->raydir_x);
	rc->dd_y = fabs(1 / rc->raydir_y);
	rc->step_x = rc->raydir_x < 0 ? -1 : 1;
	rc->step_y = rc->raydir_y < 0 ? -1 : 1;
	rc->sd_x = rc->raydir_x < 0 ? (g->pos_x - rc->map_x) * rc->dd_x : \
									(rc->map_x + 1.0 - g->pos_x) * rc->dd_x;
	rc->sd_y = rc->raydir_y < 0 ? (g->pos_y - rc->map_y) * rc->dd_y : \
									(rc->map_y + 1.0 - g->pos_y) * rc->dd_y;
}

static void calc_dda(t_game *g, t_raycast *rc)
{
	int		hit;

	hit = 0;
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

static void	calc_texture_first(t_game *g, t_raycast *rc)
{
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
	rc->l_height = rc->pwd == 0 ? 0 : (int)(g->height / rc->pwd);
	rc->draw_start = g->height / 2 - rc->l_height / 2;
	rc->draw_end = g->height / 2 + rc->l_height / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	if (rc->draw_end >= g->height)
		rc->draw_end = g->height - 1;

	rc->tex_x = (int)((rc->wall_x - floor(rc->wall_x)) * (double)TEX_WIDTH);
	if (rc->tex_num == 1 || rc->tex_num == 2)
		rc->tex_x = TEX_WIDTH - rc->tex_x - 1;
	rc->step = 1.0 * TEX_HEIGHT / rc->l_height;
	rc->tex_pos = (rc->draw_start - g->height / 2 + rc->l_height / 2) * rc->step;
}



static void		distance_sprite(t_game *g, t_sprite *s)
{
	for (int i = 0; i < s->num; i++)
	{
		s->sprite_dist[i] = (g->pos_x - s->loc_sprite[i][0]) * (g->pos_x - s->loc_sprite[i][0])
							+ (g->pos_y - s->loc_sprite[i][1]) * (g->pos_y - s->loc_sprite[i][1]);
	}
}

static void		sort_sprite(t_game *g, t_sprite *s)
{
	double	x, y;
	double	sprite_dist_tmp;

	distance_sprite(g, s);
	for (int i = 0; i < s->num; i++)
	{
		for (int j = 0; j < s->num - 1; j++)
		{
			if (s->sprite_dist[j] < s->sprite_dist[j + 1])
			{
				x = s->loc_sprite[j][0];
				y = s->loc_sprite[j][1];
				s->loc_sprite[j][0] = s->loc_sprite[j + 1][0];
				s->loc_sprite[j][1] = s->loc_sprite[j + 1][1];
				s->loc_sprite[j + 1][0] = x;
				s->loc_sprite[j + 1][1] = y;
				sprite_dist_tmp = s->sprite_dist[j];
				s->sprite_dist[j] = s->sprite_dist[j + 1];
				s->sprite_dist[j + 1] = sprite_dist_tmp;
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
	sort_sprite(g, s);
}

static void sprite(t_game *g, t_sprite *s)
{
	int		i;

	make_sprite_array(g, s);
	for (int i = 0; i < s->num; i++)
	{
		printf("[%lf] [%lf] [%lf]\n", s->loc_sprite[i][0], s->loc_sprite[i][1], s->sprite_dist[i]);
	}
	i = 0;
	while (i < s->num)
	{
		s->sprite_x = s->loc_sprite[i][0] - g->pos_x;
		s->sprite_y = s->loc_sprite[i][1] - g->pos_y;

		s->invdet = 1.0 / (g->plane_x * g->dir_y - g->dir_x * g->plane_y);
		s->trans_x = s->invdet * (g->dir_y * s->sprite_x - g->dir_x * s->sprite_y);
		s->trans_y = s->invdet * (-g->plane_y * s->sprite_x + g->plane_x * s->sprite_y);
		// spriteScreenX
		s->screen_x = (int)(g->width / 2) * (1 + s->trans_x / s->trans_y);

		s->v_move_screen = (int)(vMove / s->trans_y);

		s->sprite_height = (int)fabs((g->height / s->trans_y) / vDiv);
		s->draw_start_y = -s->sprite_height / 2 + g->height / 2 + s->v_move_screen;
		if(s->draw_start_y < 0)
			s->draw_start_y = 0;
		s->draw_end_y = s->sprite_height / 2 + g->height / 2 + s->v_move_screen;
		if(s->draw_end_y >= g->height)
			s->draw_end_y = g->height;

		s->sprite_width = (int)fabs((g->height / s->trans_y) / uDiv);
		s->draw_start_x = -s->sprite_width / 2 + s->sprite_x;
		if(s->draw_start_x < 0)
			s->draw_start_x = 0;
		s->draw_end_x = s->sprite_width / 2 + s->sprite_x;
		if(s->draw_end_x >= g->width)
			s->draw_end_x = g->width;

		while (s->draw_start_x < s->draw_end_x)
		{
			s->tex_x = (int)((256 * (s->draw_start_x - (-s->sprite_width / 2 + s->screen_x)) * TEX_WIDTH / s->sprite_width) / 256);
			if (s->trans_y >= 0 && s->trans_y < g->zbuf[s->draw_start_x])
			{
				int y = s->draw_start_y - 1;
				while (++y < s->draw_end_y)
				{
					s->d = (y - s->v_move_screen) * 256 - g->height * 128 + s->sprite_height * 128;
					s->tex_y = ((s->d * TEX_HEIGHT) / s->sprite_height) / 256;
					s->color = g->texture[4][TEX_HEIGHT * s->tex_x + s->tex_y];
					// if (s->color & 0x00FFFFFF != 0)
					// 	g->img.addr[y * g->img.size_l / 4 + s->draw_start_x] = s->color;
				}
			}
			s->draw_start_x++;
		}
		i++;
	}
}
void	calc(t_game *g)
{
	t_raycast	rc;
	int			x;

	x = 0;
	while (x < g->width)
	{
		calc_beginning(g, &rc, x);
		calc_dda(g, &rc);
		verLine(g, x, 0, g->height / 2, g->c_color);
		verLine(g, x, g->height / 2, g->height, g->f_color);
		calc_texture_first(g, &rc);
		for(int y = rc.draw_start; y < rc.draw_end; y++)
		{
			rc.tex_y = (int)rc.tex_pos & (TEX_HEIGHT - 1);
			rc.tex_pos += rc.step;
			rc.color = g->texture[rc.tex_num][TEX_HEIGHT * rc.tex_y + rc.tex_x];
			if(rc.side == 1) rc.color = (rc.color >> 1) & 8355711;
			g->img.addr[y * g->img.size_l / 4 + x] = rc.color;
		}
		g->zbuf[x] = rc.pwd;
		x++;
	}
	sprite(g, g->sprite);
	// mlx_sync(MLX_SYNC_IMAGE_WRITABLE, g->img.img);
	// mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
	// mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, g->win);
	game_display(g);

}

// void	calc(t_game *g)
// {
// 	t_raycast	rc;
// 	int			x;

// 	x = 0;

// 	while (x < g->width)
// 	{
// 		calc_beginning(g, &rc, x);
// 		calc_dda(g, &rc);
// 		verLine(g, x, 0, g->height / 2, g->c_color);
// 		verLine(g, x, g->height / 2, g->height, g->f_color);
// 		calc_texture_first(g, &rc);
// 		for(int y = rc.draw_start; y < rc.draw_end; y++)
// 		{
// 			rc.tex_y = (int)rc.tex_pos & (TEX_HEIGHT - 1);
// 			rc.tex_pos += rc.step;
// 			rc.color = g->texture[rc.tex_num][TEX_HEIGHT * rc.tex_y + rc.tex_x];
// 			if(rc.side == 1) rc.color = (rc.color >> 1) & 8355711;
// 			g->img.addr[y * g->img.size_l / 4 + x] = rc.color;
// 		}
// 		x++;
// 	}
// 	game_display(g);
// }



