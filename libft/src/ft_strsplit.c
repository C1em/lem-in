/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 11:17:16 by coremart          #+#    #+#             */
/*   Updated: 2018/11/13 16:53:06 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_countc(const char *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	if (s)
	{
		while (s[i])
		{
			if (s[i] != c && (s[i + 1] == c || s[i + 1] == 0))
				count++;
			i++;
		}
		return (count);
	}
	return (0);
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	int		size;
	char	**tab;

	i = 0;
	j = 0;
	size = 0;
	if (s)
	{
		if (!(tab = (char**)malloc(sizeof(char*) * (ft_countc(s, c) + 1))))
			return (NULL);
		while (s[i])
		{
			size = ft_strclen(&s[i], c);
			if (size)
				tab[j++] = ft_strndup(&s[i], size);
			i += size;
			if (s[i])
				i++;
		}
		tab[j] = NULL;
		return (tab);
	}
	return (NULL);
}
