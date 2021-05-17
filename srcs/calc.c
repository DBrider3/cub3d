/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:47:56 by dcho              #+#    #+#             */
/*   Updated: 2021/05/18 00:05:13 by dcho             ###   ########.fr       */
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
	// rc->tex_pos = 0.0;
}

void	calc(t_game *g)
{
	t_raycast	rc;
	int			x;

	x = 0;
	// ft_bzero(&rc, sizeof(rc));
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
		x++;
	}
	game_display(g);
}

// void	calc(t_game *g, t_raycast *rc)
// {
// 	int			x;

// 	x = 0;
// 	while (x <g->width)
// 	{
// 		rc->camera_x = 2 * x / (double)g->width - 1;
// 		rc->raydir_x = g->dir_x + g->plane_x * rc->camera_x;
// 		rc->raydir_y = g->dir_y + g->plane_y * rc->camera_x;

// 		rc->map_x = (int)g->pos_x;
// 		rc->map_y = (int)g->pos_y;

// 		rc->dd_x = fabs(1 / rc->raydir_x);
// 		rc->dd_y = fabs(1 / rc->raydir_y);

// 		rc->step_x = rc->raydir_x < 0 ? -1 : 1;
// 		rc->step_y = rc->raydir_y < 0 ? -1 : 1;
// 		rc->sd_x = rc->raydir_x < 0 ? (g->pos_x - rc->map_x) * rc->dd_x : \
// 									(rc->map_x + 1.0 - g->pos_x) * rc->dd_x;
// 		rc->sd_y = rc->raydir_y < 0 ? (g->pos_y - rc->map_y) * rc->dd_y : \
// 									(rc->map_y + 1.0 - g->pos_y) * rc->dd_y;
// 		int hit = 0; //was there a wall hit?
// 		while (hit == 0)
// 		{
// 			if (rc->sd_x < rc->sd_y)
// 			{
// 				rc->sd_x += rc->dd_x;
// 				rc->map_x += rc->step_x;
// 				rc->side = 0;
// 			}
// 			else
// 			{
// 				rc->sd_y += rc->dd_y;
// 				rc->map_y += rc->step_y;
// 				rc->side = 1;
// 			}
// 			if (g->map->map[rc->map_x][rc->map_y] == '1')
// 				hit = 1;
// 		}
// 		verLine(g, x, 0, g->height / 2, g->c_color);
// 		verLine(g, x, g->height / 2, g->height, g->f_color);

// 		if (rc->side == 0)
// 		{
// 			rc->pwd = (rc->map_x - g->pos_x + (1 - rc->step_x) / 2) / rc->raydir_x;
// 			rc->tex_num = rc->step_x > 0 ? 1 : 0;
// 			rc->wall_x = g->pos_y + rc->pwd * rc->raydir_y;
// 		}
// 		else
// 		{
// 			rc->pwd = (rc->map_y - g->pos_y + (1 - rc->step_y) / 2) / rc->raydir_y;
// 			rc->tex_num = rc->step_y > 0 ? 3 : 2;
// 			rc->wall_x = g->pos_x + rc->pwd * rc->raydir_x;
// 		}

// 		if (rc->pwd == 0)
// 			rc->l_height = 0;
// 		else
// 		{
// 			rc->l_height = (int)(g->height / rc->pwd);
// 		}

// 		// rc->l_height = rc->pwd == 0 ? 0 : (int)(g->height / rc->pwd);

// 		rc->draw_start = -(rc->l_height) / 2 + g->height / 2; // 혹시?

// 		if (rc->draw_start < 0)
// 			rc->draw_start = 0;
// 		rc->draw_end = rc->l_height / 2 + g->height / 2;
// 		if (rc->draw_end >= g->height)
// 			rc->draw_end = g->height - 1;

// 		rc->wall_x -= floor((rc->wall_x)); // 혹시?
// 		rc->tex_x = (int)(rc->wall_x * (double)TEX_WIDTH);
// 		if (rc->tex_num == 1 || rc->tex_num == 2)
// 			rc->tex_x = TEX_WIDTH - rc->tex_x - 1;
// 		rc->step = 1.0 * TEX_HEIGHT / rc->l_height;
// 		rc->tex_pos = (rc->draw_start - g->height / 2 + rc->l_height / 2) * rc->step;

// 		for(int y = rc->draw_start; y < rc->draw_end; y++)
// 		{
// 			rc->tex_y = (int)(rc->tex_pos) & (TEX_HEIGHT - 1);
// 			rc->tex_pos += rc->step;
// 			rc->color = g->texture[rc->tex_num][TEX_HEIGHT * rc->tex_y + rc->tex_x];
// 			if(rc->side == 1)
// 				rc->color = (rc->color >> 1) & 8355711;

// 			g->img.addr[y * g->img.size_l / 4 + x] = rc->color;
// 		}
// 		x++;
// 	}
// 	game_display(g);
// }



