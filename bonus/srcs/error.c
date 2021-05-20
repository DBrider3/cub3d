/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 22:02:04 by dcho              #+#    #+#             */
/*   Updated: 2021/05/20 15:28:08 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		exit_btn(void)
{
	exit(0);
}

int		exit_error(char *s)
{
	printf("Error\n: %s\n", s);
	exit(0);
}