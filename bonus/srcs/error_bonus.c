/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 22:02:04 by dcho              #+#    #+#             */
/*   Updated: 2021/05/21 22:06:47 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void		stop_music(void)
{
	system("killall afplay");
}

int		exit_btn(void)
{
	stop_music();
	exit(0);
}

int				exit_error(char *s)
{
	printf("Error\n: %s\n", s);
	exit(0);
}
