/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 20:29:43 by dcho              #+#    #+#             */
/*   Updated: 2020/11/06 20:04:17 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		j;
	size_t		ii;
	size_t		needle_len;

	i = 0;
	needle_len = ft_strlen(needle);
	if (!*needle)
		return ((char*)haystack);
	while (i < len)
	{
		ii = i;
		j = 0;
		while (*(needle + j) && ii < len)
		{
			if (*(haystack + ii) != *(needle + j))
				break ;
			j++;
			ii++;
		}
		if (j == needle_len)
			return ((char*)haystack + i);
		i++;
	}
	return (0);
}
