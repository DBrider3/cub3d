/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 21:22:52 by dcho              #+#    #+#             */
/*   Updated: 2021/05/20 07:11:29 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		final_free(t_options *op, t_game *g)
{
	del_map(op->map);
	free(op->no);
	free(op->so);
	free(op->we);
	free(op->ea);
	free(op->s);
	free(g->zbuf);
	free(g->sprite->sprite_dist);
}
