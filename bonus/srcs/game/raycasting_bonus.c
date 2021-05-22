/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 06:13:54 by dcho              #+#    #+#             */
/*   Updated: 2021/05/20 17:44:45 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	calc_raycasing(t_game *g, t_raycast *rc, int x)
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

static void	calc_dda(t_game *g, t_raycast *rc)
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

static void	calc_texture(t_game *g, t_raycast *rc)
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
	rc->tex_pos = (rc->draw_start - g->height / 2 + rc->l_height / 2)
					* rc->step;
}

void		raycasting_main(t_game *g)
{
	t_raycast	rc;
	int			x;

	x = -1;
	while (++x < g->width)
	{
		calc_raycasing(g, &rc, x);
		calc_dda(g, &rc);
		draw_color(g, x, g->c_color, 1);
		draw_color(g, x, g->f_color, 0);
		calc_texture(g, &rc);
		draw_texture(g, &rc, x);
		g->zbuf[x] = rc.pwd;
	}
}
