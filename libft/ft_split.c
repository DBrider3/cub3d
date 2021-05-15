/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:02:47 by dcho              #+#    #+#             */
/*   Updated: 2020/11/11 19:43:47 by dcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			c_cnt(char const *s, char c)
{
	int		cnt;
	int		i;

	i = 0;
	cnt = 0;
	while (*(s + i))
	{
		if (*(s + i) == c)
		{
			while (*(s + i) == c)
				i++;
		}
		else
		{
			if (i == 0)
			{
				if (*(s + i) != c)
					cnt++;
			}
			else if (*(s + i - 1) == c && *(s + i) != 0)
				cnt++;
			i++;
		}
	}
	return (cnt);
}

char const	*input_table(char const *s, char c, char **res)
{
	char	*end;
	int		len;
	int		i;

	while (1)
	{
		if (*s == c)
			s++;
		else
			break ;
	}
	end = ft_strchr(s, c);
	if (end == 0)
		end = ft_strchr(s, 0);
	len = end - s + 1;
	if (!(*res = malloc(sizeof(char) * len)))
		return (NULL);
	i = 0;
	while (i < len - 1)
		(*res)[i++] = *s++;
	(*res)[i] = 0;
	s++;
	return (s);
}

char		**ft_split(char const *s, char c)
{
	int		cnt;
	char	**res;
	int		i;
	int		j;

	cnt = c_cnt(s, c);
	if (!(res = malloc(sizeof(char*) * (cnt + 1))))
		return (NULL);
	i = 0;
	while (i < cnt)
	{
		if ((s = input_table(s, c, &res[i++])) == NULL)
		{
			j = 0;
			while (j < i)
				free(res[j]);
			return (NULL);
		}
	}
	res[i] = NULL;
	i = 0;
	return (res);
}
