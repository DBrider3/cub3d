/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 15:30:55 by dcho              #+#    #+#             */
/*   Updated: 2020/11/14 21:31:47 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	size_t		i;

	i = 0;
	if ((unsigned char*)dst == 0 && (unsigned char*)src == 0)
		return (0);
	while (i < n)
	{
		*((unsigned char*)dst + i) = *((unsigned char*)src + i);
		i++;
	}
	return (dst);
}
