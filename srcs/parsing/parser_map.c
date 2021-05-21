/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 22:35:39 by dcho              #+#    #+#             */
/*   Updated: 2021/05/21 12:44:24 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 맵 생성
int				new_map(t_map **m)
{
	if (!(*m = malloc(sizeof(t_map))))
		return (ERROR);
	// 초기 임의값으로 초기화
	if (!((*m)->map = malloc(sizeof(char*) * INITAIL_SIZE)))
		return (ERROR);
	/*
	index	: 실제로 맵 index가 어디까지 있는지
	size 	: 맵이 어느정도 할당 되어있는지
	max_col	: 맵에 젤 큰 길이
	*/
	(*m)->index = 0;
	(*m)->size = INITAIL_SIZE;
	(*m)->max_col = 0;
	return (NO_ERROR);
}

// 맵 확장
static int		expand_map(t_map *m)
{
	char	**map;
	int		i;

	// 기존 맵 map 에 잠시 저장
	map = m->map;
	// 사이즈 2배로 늘려줌
	m->size *= 2;
	// 맵 다시 사이즈 늘려서 할당 해줌
	if (!(m->map = malloc(sizeof(char*) * m->size)))
	{
		free(map);
		return (ERROR);
	}
	i = 0;
	// 저장되어있는 맵 사이즈 늘린 맵에 넣어줌
	while (i < m->index)
	{
		m->map[i] = map[i];
		i++;
	}
	free(map);
	return (NO_ERROR);
}

// 맵에 라인 추가
int				add_map_line(t_map *m, char *line)
{
	int		len;

	// index와 size가 같으면 확장해줌
	if (m->index == m->size && expand_map(m))
		return (ERROR);
	// 맵에 젤 큰 길이 갱신
	len = ft_strlen(line);
	if (m->max_col < len)
		m->max_col = len;
	// 맵에 라인 추가
	m->map[m->index] = line;
	m->index++;
	return (NO_ERROR);
}

// 맵 삭제
void			del_map(t_map *m)
{
	int		i;

	i = 0;
	while (i < m->index)
		free(m->map[i++]);
	free(m->map);
	free(m);
}

int				find_map(char *line, int *flag, t_options *op)
{
	int		i;

	i = 0;
	while (*(line + i))
	{
		// '1' 찾기 시작하면 맵으로 인식하고 파싱
		if (*(line + i) == '1')
		{
			if (add_map_line(op->map, ft_strdup(line)))
				return (ERROR);
			// 맵 찾으면 flag값 변화
			*flag = 1;
			break ;
		}
		// 빈칸이면 인덱스 증가
		else if (*(line + i) == ' ')
			;
		// '1', ' ' 다른걸로 맵에 그려져 있으면 에러
		else
			exit_error("not the correct parsing");
		i++;
	}
	return (NO_ERROR);
}
