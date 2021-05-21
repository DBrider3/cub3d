/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 22:12:38 by dcho              #+#    #+#             */
/*   Updated: 2021/05/21 11:41:50 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		parse_sub(t_options *op, char *line, int *flag)
{
	// 1. 식별자 모두 들어왔는지 체크
	if (!(check_identifier(*op)))
	{
		// 식별자 파싱
		if (parse_identifier(line, op))
			return (free_value(line) + ERROR);
	}
	// 2. 식별자가 모두 차 있으면 맵 찾기
	else if (*flag == 0)
	{
		// 맵 찾기 함수 호출
		if (find_map(line, flag, op))
			return (free_value(line) + ERROR);
	}
	// 3. 맵을 찾았다면 맵 파싱
	else
	{
		// gnl로 받은 문자열 맵에 추가
		if (add_map_line(op->map, ft_strdup(line)))
			return (free_value(line) + ERROR);
	}
	free(line);
	return (NO_ERROR);
}

int				parse_main(char *f, t_options *op, t_game *g, t_sprite *s)
{
	char	*line;
	int		ret;
	int		flag;
	int		fd;

	// 파일 open
	if ((fd = open(f, O_RDONLY)) == -1)
		return (ERROR);
	// 각 구조체, 변수 초기화
	init_start(op, g, s);
	// 맵 공간 생성
	if (new_map(&op->map))
		return (ERROR);
	// flag로 맵 첫부분인지 체크
	flag = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		// gnl으로 받은 line 문자열 파싱
		if (parse_sub(op, line, &flag))
			return (ERROR);
	}
	// 라인프리, 파일디스크럽터 종료
	free(line);
	close(fd);
	// 맵 주소 game 구조체에 옮기기
	g->map = op->map;
	// 맵 유효성 체크
	map_check_main(op->map, g);
	return (NO_ERROR);
}
