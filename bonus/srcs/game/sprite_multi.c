/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_multi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 18:02:02 by dcho              #+#    #+#             */
/*   Updated: 2021/05/20 18:05:41 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"


void	sort_texture_num(t_sprite *s, int index)
{
	int		tmp;

	tmp = s->tex_num[index];
	s->tex_num[index] = s->tex_num[index + 1];
	s->tex_num[index + 1] = tmp;
}
