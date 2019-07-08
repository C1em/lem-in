/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 18:10:52 by coremart          #+#    #+#             */
/*   Updated: 2018/11/16 13:07:00 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;

	i = 0;
	if (s)
	{
		if (!(res = (char*)malloc(len + 1)))
			return (NULL);
		while (i < len)
		{
			res[i] = s[start + i];
			i++;
		}
		res[i] = 0;
		return (res);
	}
	return (NULL);
}
