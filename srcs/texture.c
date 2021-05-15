/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 22:37:38 by dcho              #+#    #+#             */
/*   Updated: 2021/05/14 17:41:25 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_image(t_game *g, int *texture, char *path, t_img *img)
{
	int		y;
	int		x;

	img->img = mlx_xpm_file_to_image(g->mlx, path, &img->img_width,
									&img->img_height);
	img->addr = (int*)mlx_get_data_addr(img->img, &img->bpp, &img->size_l,
										&img->endian);
	y = 0;
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			texture[img->img_width * y + x] = img->addr[img->img_width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(g->mlx, img->img);
}

void	load_texture(t_game *g, t_options *op)
{
	t_img	img;

	load_image(g, g->texture[0], op->no, &img);
	load_image(g, g->texture[1], op->so, &img);
	load_image(g, g->texture[2], op->we, &img);
	load_image(g, g->texture[3], op->ea, &img);
	load_image(g, g->texture[4], op->s, &img);
}
