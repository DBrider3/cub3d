#include "mlx.h"
#include <stdio.h>

typedef struct     s_mlx
{
    void        *mlx;
    void        *win;
}                t_mlx;

typedef struct     s_data {
    void		*img;
    char		*addr;
    int			bits_per_pixel;
    int			line_length;
    int			endian;
}                t_data;



int		main(void)
{
	t_mlx	mlx;
	t_data	data;
	//     char        map[10][10] = {
    //     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    //     {1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    //     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    // };

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 600, 400, "mlx");
	data.img = mlx_new_image(mlx.mlx, 256,256);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
                &data.line_length, &data.endian);
	for (int i = 0; i < 256; i++)
        for (int j = 0; j < (data.line_length / 4); j++)
            data.addr[i * (data.line_length / 4) + j] = 0x00FFFFFF;
	printf("%d %d %d\n", data.bits_per_pixel, data.line_length, data.endian);

	int		xy[2];
	void	*img_xpm;

	img_xpm = mlx_xpm_file_to_image(mlx.mlx, "./wall_e.xpm", &xy[0], &xy[1]);

	mlx_put_image_to_window(mlx.mlx, mlx.win, data.img, 0, 0);
	mlx_put_image_to_window(mlx.mlx, mlx.win, img_xpm, 256, 256);
	mlx_loop(mlx.mlx);
	// mlx_hook(mlx.win, )
}
