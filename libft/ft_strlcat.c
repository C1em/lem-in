/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:14:43 by coremart          #+#    #+#             */
/*   Updated: 2018/11/16 13:50:38 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int i;
	unsigned int j;
	unsigned int k;

	i = ft_strlen(dst);
	j = ft_strlen(src);
	k = 0;
	j += ft_min(i, size);
	while (src[k] != '\0' && (i + k + 1 < size))
	{
		dst[i + k] = src[k];
		k++;
	}
	dst[i + k] = '\0';
	return (j);
}
