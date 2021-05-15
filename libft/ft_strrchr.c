/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 20:21:22 by dcho              #+#    #+#             */
/*   Updated: 2020/11/04 20:28:06 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;

	len = ft_strlen(s);
	if (c == 0)
		return ((char*)(s + len));
	len -= 1;
	while (len != -1)
	{
		if (*(s + len) == c)
			return ((char*)(s + len));
		len--;
	}
	return (0);
}
