/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 11:23:25 by coremart          #+#    #+#             */
/*   Updated: 2018/11/16 13:05:27 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *h, const char *n, size_t len)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	if (n[j] == '\0')
		return ((char*)h);
	while (h[i] && i < len)
	{
		while (h[i + j] == n[j] && h[i + j] && i + j < len)
		{
			j++;
			if (n[j] == '\0')
				return ((char *)&h[i]);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
