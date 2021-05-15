/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 17:23:13 by dcho              #+#    #+#             */
/*   Updated: 2020/11/14 21:31:51 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;

	if ((unsigned char*)dst == 0 && (unsigned char*)src == 0)
		return (0);
	if (dst < src)
	{
		i = 0;
		while (i < len)
		{
			*((unsigned char*)dst + i) = *((unsigned char*)src + i);
			i++;
		}
	}
	else
	{
		i = len - 1;
		while (i + 1 > 0)
		{
			*((unsigned char*)dst + i) = *((unsigned char*)src + i);
			i--;
		}
	}
	return (dst);
}
