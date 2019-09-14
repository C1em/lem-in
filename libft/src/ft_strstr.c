/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 11:01:54 by coremart          #+#    #+#             */
/*   Updated: 2018/11/16 13:06:19 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (needle[j] == '\0')
		return ((char*)haystack);
	while (haystack[i])
	{
		while (haystack[i + j] == needle[j] && haystack[i + j])
		{
			j++;
			if (needle[j] == '\0')
				return ((char*)&haystack[i]);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
