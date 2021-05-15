#include "mlx.h"
#include <stdio.h>

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int			key_hook(int keycode, int *p_cnt)
{
	printf("key_hook...%d\n", keycode);
	*p_cnt += 1;
	return (0);
}

int             main(void)
{
    void    *mlx;
    void    *mlx_win;
    t_data  img;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 600, 400, "Hello world!");
    // img.img = mlx_new_image(mlx, 600, 400);
    // img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
    //                              &img.endian);
    // for (int i = 0; i <= 5; i++)
	// my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);

	// int k = 60;
	// for (int y = 60; y < 100; y++)
	// {
	// 	for (int x = 0; x < y; x++)
	// 	{
	// 		my_mlx_pixel_put(&img, x, y, 0);
	// 		if (x < k)
	// 		{
	// 			my_mlx_pixel_put(&img, k, y, 0x00FF0000);
	// 		}

	// 	}

	// 	// for (int tmp = )
	// }
	// for (int y = 60; y < 180; y++)
	// {
	// 	for (int x = 60; x < y; x++)
	// 		my_mlx_pixel_put(&img, x, y, 0x00FF0000);// 붉은색 선을 대각선으로 그린다.
	// }
	// for (int i = 50; i < 150; i++)
	// {
	// 	for (int j = i - 50; j <= (2 * (i - 50)) + 1; j++)
	// 		my_mlx_pixel_put(&img, j, i, 0x00FF0000);// 붉은색 선을 대각선으로 그린다.
	// }
	// for(int i = 70; i < 150 ; i++) {
	// 	for (int j = i; j < 150; j++)
	// 		my_mlx_pixel_put(&img, i, j, 0x00FF0000);// 붉은색 선을 대각선으로 그린다.
	// 	// my_mlx_pixel_put(&img, 5, i, 0x00FF0000);// 붉은색 선을 세로으로 그린다.
	// 	// my_mlx_pixel_put(&img, i, 5, 0x00FF0000);// 붉은색 선을 가로으로 그린다.
	// }
	// for (int i = 0; i < 70; i++)
	// {

	// }
    // mlx_put_image_to_window(mlx, mlx_win0, img.img, 0, 0);
	int cnt = 0;
	mlx_key_hook(mlx_win, &key_hook, &cnt);
    mlx_loop(mlx);
}

