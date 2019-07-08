/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 10:35:22 by coremart          #+#    #+#             */
/*   Updated: 2018/11/16 13:48:35 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	size;
	size_t	i;
	char	*dst;

	size = (size_t)ft_min(ft_strlen(s), (int)n);
	i = 0;
	if (!(dst = (char*)malloc(size + 1)))
		return (NULL);
	while (i < size)
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
