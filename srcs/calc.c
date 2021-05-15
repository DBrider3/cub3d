/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:47:56 by dcho              #+#    #+#             */
/*   Updated: 2021/05/15 21:58:38 by dcho             ###   ########.fr       */
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

void	calc(t_game *info)
{
	int	x;

	x = 0;
	while (x < info->width)
	{
		double cameraX = 2 * x / (double)info->width - 1;
		double rayDirX = info->dirx + info->planex * cameraX;
		double rayDirY = info->diry + info->planey * cameraX;

		int mapX = (int)info->posx;
		int mapY = (int)info->posy;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		 //length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);


		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (info->posx - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - info->posx) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (info->posy - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - info->posy) * deltaDistY;
		}

		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			// printf("%c\n", info->map->map[mapX][mapY]);
			//Check if ray has hit a wall

			if (info->map->map[mapX][mapY] == '1') hit = 1;
		}

		verLine(info, x, 0, info->height / 2, info->c_color);
		verLine(info, x, info->height / 2, info->height, info->f_color);


		int lineheight;
		int	texnum;
		int drawstart;
		double perpwalldist;
		double wallX; //where exactly the wall was hit


		if (side == 0)
		{
			perpwalldist = (mapX - info->posx + (1 - stepX) / 2) / rayDirX;
			texnum = stepX > 0 ? 1 : 0;
			wallX = info->posy + perpwalldist * rayDirY;
		}
		else
		{
			perpwalldist = (mapY - info->posy + (1 - stepY) / 2) / rayDirY;
			texnum = stepY > 0 ? 3 : 2;
			wallX = info->posx + perpwalldist * rayDirX;
		}


		//Calculate height of line to draw on screen
		if (perpwalldist == 0)
			lineheight = 0;
		else
			lineheight = (int)(info->height / perpwalldist);

		//calculate lowest and highest pixel to fill in current stripe
		drawstart = -lineheight / 2 + info->height / 2;
		if(drawstart < 0)
			drawstart = 0;
		int drawEnd = lineheight / 2 + info->height / 2;
		if(drawEnd >= info->height)
			drawEnd = info->height - 1;

		wallX -= floor((wallX));
		//x coordinate on the texture
		int texX = (int)(wallX * (double)texWidth);
		if (texnum == 1 || texnum == 2)
			texX = texWidth - texX - 1;

		double step = 1.0 * texHeight / lineheight;
		// Starting texture coordinate
		double texPos = (drawstart - info->height / 2 + lineheight / 2) * step;
		for(int y = drawstart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			int color = info->texture[texnum][texHeight * texY + texX];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if(side == 1) color = (color >> 1) & 8355711;
			// info->buf[y][x] = color;

			info->img.addr[y * info->img.size_l / 4 + x] = color;
		}
		x++;
	}
	game_display(info);
}



