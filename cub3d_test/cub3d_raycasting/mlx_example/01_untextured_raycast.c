/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_untextured_raycast.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 12:12:25 by yohan             #+#    #+#             */
/*   Updated: 2021/05/14 22:13:36 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "key_macos.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_RELEASE	3
#define X_EVENT_KEY_EXIT	17
#define mapWidth 24
#define mapHeight 24
#define width 640
#define height 480

typedef struct	s_info
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	void	*mlx;
	void	*win;
	double	moveSpeed;
	double	rotSpeed;
}				t_info;

int	worldMap[24][24] = {
							{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
							{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
							{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
						};

void	verLine(t_info *info, int x, int y1, int y2, int color)
{
	int	y;

	y = y1;
	while (y < y2)
	{
		mlx_pixel_put(info->mlx, info->win, x, y, color);
		y++;
	}
}

void	calc(t_info *info)
{
	int	x;

	x = 0;
	printf("test\n");
	while (x < width)
	{
		double cameraX = 2 * x / (double)width - 1;
		/*
		카메라 X는 카메라 평면에서 차지하는 X좌표를 의미, 배수
		스크린의 어디쪽에 있는지 알려줌
		*/
		double rayDirX = info->dirX + info->planeX * cameraX;
		double rayDirY = info->dirY + info->planeY * cameraX;
		/*
		광선의 방향벡터 구하기 (방향 벡터 + 카메라평면 * 배수)
		*/
		int mapX = (int)info->posX;
		int mapY = (int)info->posY;
		/*
		소수점인 위치를 맵상 어느 칸에 있는지 저장
		*/
		double sideDistX;
		double sideDistY;
		/*
		sideDist 벡터 선언 (시작점 ~ 첫번째 만나는 면)
		*/
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;
		/*
		deltaDist 벡터는 공식으로 구함. 일정한 비율이기 때문에 1로 함.
		*/
		int stepX;
		int stepY;
		/*
		DDA 알고리즘에 관한 step 한칸씩 점프 하고 방향 알려줌
		*/
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		// 	side는 x,y 어떤 면에 부딪힌건지 알려줌
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (info->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - info->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (info->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - info->posY) * deltaDistY;
		}
		/*
		광선x 양수 인지 음수인지 체크 하면 방향 알아낸 뒤, 스텝 지정하고
		비례식을 이용해서 sideDist 벡터를 구해준다.
		*/
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
			//Check if ray has hit a wall
			if (worldMap[mapX][mapY] > 0) hit = 1;
		}
		printf("test2\n");
		/*
		DDA 알고리즘을 시작하는데 sideDist X, Y를 비교해서 더 짧은 것에 더하면서
		step 증가와 side 체크 하고 그게 벽에 닿으면 DDA 종료
		*/
		if (side == 0)
			perpWallDist = (mapX - info->posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY;
// printf("[perpWallDist : %lf]\n", perpWallDist);
		/*
		비례식을 이용하여 연립방정식 풀이
		*/
		//Calculate height of line to draw on screen
		int lineHeight = (int)(height / perpWallDist);
		/*
		높이와 수직거리로 나눠서 그려야 할 라인 높이를 측정한다.
		*/
		int drawStart = -lineHeight / 2 + height / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + height / 2;
		if(drawEnd >= height)
			drawEnd = height - 1;
		/*
		drawStart 변수는 높이, 라인 높이를 반 짤라 빼주는 방식,
		drawEnd는 더하는 방식, 범위를 벗어나면 처리를 해준다.
		*/
		int	color;
		if (worldMap[mapY][mapX] == 1)
			color = 0xFF0000;
		else if (worldMap[mapY][mapX] == 2)
			color = 0x00FF00;
		else if (worldMap[mapY][mapX] == 3)
			color = 0x0000FF;
		else if (worldMap[mapY][mapX] == 4)
			color = 0xFFFFFF;
		else
			color = 0xFFFF00;

		if (side == 1) // 명암 표현 함
			color = color / 2;

		verLine(info, x, 0, height / 2, 0);
		verLine(info, x, height / 2, (height - 1), 0);
		verLine(info, x, drawStart, drawEnd, color);
		x++;
// while (1);
	}
}

int	main_loop(t_info *info)
{
	calc(info);
	// mlx_put_image_to_window(info->mlx, info->win, &info->img, 0, 0);

	return (0);
}

int	key_press(int key, t_info *info)
{
	if (key == K_W)
	{
		if (!worldMap[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)])
			info->posX += info->dirX * info->moveSpeed;
		if (!worldMap[(int)(info->posX)][(int)(info->posY + info->dirY * info->moveSpeed)])
			info->posY += info->dirY * info->moveSpeed;
	}
	//move backwards if no wall behind you
	if (key == K_S)
	{
		if (!worldMap[(int)(info->posX - info->dirX * info->moveSpeed)][(int)(info->posY)])
			info->posX -= info->dirX * info->moveSpeed;
		if (!worldMap[(int)(info->posX)][(int)(info->posY - info->dirY * info->moveSpeed)])
			info->posY -= info->dirY * info->moveSpeed;
	}
	//rotate to the right
	if (key == K_D)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
		info->dirY = oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
		info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
	}
	//rotate to the left
	if (key == K_A)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
		info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
		info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
	}
	if (key == K_ESC)
		exit(0);
	return (0);
}

int	main(void)
{
	t_info info;
	info.mlx = mlx_init();

	info.posX = 12;
	info.posY = 5;
	/*
	플레이어의 위치 벡터는 맵의 EWSN 에서 추출한것의 +0.5 해주면 된다.
	이유는 중앙에 위치 시키기 위해
	*/
	info.dirX = -1;
	info.dirY = 0;
	info.planeX = 0;
	info.planeY = 0.66;
	/*
	방향벡터와 카메라 평면의 초기값 이렇게 설정해 두면 회전행렬을 통해 알아서 회전 시켜주면 된다.
	*/
	info.moveSpeed = 0.05;
	info.rotSpeed = 0.05;
	/*
	키를 입력했을때 x, y가 얼마나 이동할지 알려주는 변수이다.
	*/
	info.win = mlx_new_window(info.mlx, width, height, "mlx");
	/*
	이건 뭐 다 아는 mlx 창 생성 함수
	*/
	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, X_EVENT_KEY_RELEASE, 0, &key_press, &info);

	mlx_loop(info.mlx);
}
