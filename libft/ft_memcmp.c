/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 16:43:20 by dcho              #+#    #+#             */
/*   Updated: 2020/10/16 16:47:39 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n)
	{
		if (*((unsigned char*)s1 + i) != *((unsigned char*)s2 + i))
			return (*((unsigned char*)s1 + i) - *((unsigned char*)s2 + i));
		i++;
	}
	return (0);
}
