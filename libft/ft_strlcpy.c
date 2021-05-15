/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 17:11:52 by dcho              #+#    #+#             */
/*   Updated: 2020/11/04 19:29:11 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t		i;

	i = 0;
	while (i + 1 < size && *(src + i))
	{
		*(dest + i) = *(src + i);
		i++;
	}
	if (size != 0)
		*(dest + i) = 0;
	return (ft_strlen(src));
}
