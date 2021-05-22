/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 18:12:15 by dcho              #+#    #+#             */
/*   Updated: 2021/05/22 17:02:33 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 스크린 체크
static void		screen_check(t_options op, t_game *g)
{
	int		x;
	int		y;

	// 현재 화면 사이즈 가져오는 mlx 함수
	mlx_get_screen_size(g->mlx, &x, &y);
	// 현재 사이즈 보다 파싱한 사이즈가 더 크면 현재 사이즈 넣고 아니면 반대
	if (op.r[0] > x || op.r[1] > y)
	{
		g->width = x;
		g->height = y;
	}
	else
	{
		g->width = op.r[0];
		g->height = op.r[1];
	}
}

static void		start_mlx(t_options *op, t_game *g)
{
	// mlx 초기화
	g->mlx = mlx_init();
	// 사이즈 넣기
	screen_check(*op, g);
	// 게임시작 전 초기화
	game_main(g, op);
	// 창 만들기
	g->win = mlx_new_window(g->mlx, g->width, g->height, "dcho's cub3d");
	// 메모리에 새로운 이미지 생성
	g->img.img = mlx_new_image(g->mlx, g->width, g->height);
	// 이미지에 대한 정보를 리턴해 이미지를 수정할 수 있도록 함
	g->img.addr = (int*)mlx_get_data_addr(g->img.img, &(g->img.bpp),
					&(g->img.size_l), &(g->img.endian));
	// bmp 처리
	if (g->bmp_flag)
		save_bmp(g);
	// 게임 루프 돌기
	else
	{
		mlx_loop_hook(g->mlx, &game_loop, g);
		mlx_hook(g->win, KEY_PRESS, 0, &key_press, g);
		mlx_hook(g->win, KEY_RELEASE, 0, &key_release, g);
		mlx_hook(g->win, 17, 0, exit_btn, 0);
		mlx_loop(g->mlx);
	}
}

int				main(int argc, char *argv[])
{
	t_options	op;
	t_game		game;
	t_sprite	s;
	char		*file_extension;

	//	인자 개수 안맞을때
	if (argc < 2 || argc > 3)
		exit_error("argument number is not appropriate");
	else
	{
		// 첫번째 인자 확장자 체크를 위한 문자열 주소값 받아오기
		file_extension = argv[1] + (ft_strlen(argv[1]) - 4);
		// ".cub" 확장자 체크
		if (ft_strncmp(file_extension, ".cub", 5))
			exit_error("first argument is not correct");
		// 파싱하고 이상 생기면 에러
		if (parse_main(argv[1], &op, &game, &s) == ERROR)
			exit_error("not the correct parsing");
	}
	// 인자가 2개 들어올시
	if (argc == 3)
	{
		// bmp_flag 먼저 체크 해주기
		game.bmp_flag = 1;
		// "--save" 인자가 아니면 에러
		if (ft_strncmp(argv[2], "--save", ft_strlen(argv[2]) + 1))
			exit_error("second argument is not correct");
	}
	// 본격적인 mlx 시작
	start_mlx(&op, &game);
	final_free(&op, &game);
	return (0);
}
