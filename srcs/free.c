/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 21:22:52 by dcho              #+#    #+#             */
/*   Updated: 2021/05/21 13:29:45 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_free(int **s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

static void	all_free(t_game *g)
{
	if (g->img.img)
		mlx_destroy_image(g->mlx, g->img.img);
	if (g->zbuf)
		free_value(g->zbuf);
	if (g->texture)
		ft_free(g->texture);
	exit(0);
}

void		final_free(t_options *op, t_game *g)
{
	del_map(op->map);
	free(op->no);
	free(op->so);
	free(op->we);
	free(op->ea);
	free(op->s);
	all_free(g);
}
