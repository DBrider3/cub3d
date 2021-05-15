/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 16:39:30 by dcho              #+#    #+#             */
/*   Updated: 2020/11/12 19:25:25 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *restrict dst,\
const void *restrict src, int c, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n)
	{
		*((unsigned char*)dst + i) = *((unsigned char*)src + i);
		if (*((unsigned char*)src + i) == (unsigned char)c)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
