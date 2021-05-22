/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 10:10:02 by dcho              #+#    #+#             */
/*   Updated: 2021/05/20 17:44:24 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void		input_header(t_game *g, int fd)
{
	unsigned char	header[54];

	ft_bzero(header, 54);
	header[0] = 'B';
	header[1] = 'M';
	*(unsigned int*)&header[2] = (g->width * g->height * 4) + 54;
	header[10] = 0x36;
	header[14] = 0x28;
	*(unsigned int*)&header[18] = (g->width);
	*(unsigned int*)&header[22] = (g->height);
	header[26] = 0x01;
	header[28] = 32;
	header[34] = g->width * g->height * 4;
	if (write(fd, header, 54) == -1)
		exit_error("write error");
}

static void		input_data(t_game *g, int fd)
{
	int		i;
	int		j;

	i = g->height;
	while (--i >= 0)
	{
		j = -1;
		while (++j < g->width)
			write(fd, &g->img.addr[i * g->img.size_l / 4 + j], 4);
	}
}

void			save_bmp(t_game *g)
{
	int		fd;

	raycasting_main(g);
	sprite_main(g, g->sprite);
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
	if ((fd = open("cub3D.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
		exit_error("file open error");
	input_header(g, fd);
	input_data(g, fd);
}
