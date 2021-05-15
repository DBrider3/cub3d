/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 20:44:06 by dcho              #+#    #+#             */
/*   Updated: 2020/11/04 21:13:17 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*t_s1;
	unsigned char	*t_s2;
	size_t			len;
	size_t			i;

	t_s1 = (unsigned char*)s1;
	t_s2 = (unsigned char*)s2;
	i = 0;
	len = ft_strlen(s1) > ft_strlen(s2) ? ft_strlen(s1) : ft_strlen(s2);
	while (i < len && i < n)
	{
		if (*(t_s1 + i) != *(t_s2 + i))
			return (*(t_s1 + i) - *(t_s2 + i));
		i++;
	}
	if (n != 0)
		return (*(t_s1 + i - 1) - *(t_s2 + i - 1));
	else
		return (0);
}
