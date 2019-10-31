/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 16:47:00 by coremart          #+#    #+#             */
/*   Updated: 2019/10/13 11:05:43 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*uc_dst;
	unsigned char	*uc_src;
	size_t			i;

	uc_dst = (unsigned char*)dst;
	uc_src = (unsigned char*)src;
	if (uc_src == uc_dst)
		return (dst);
	if (uc_src > uc_dst && uc_dst + len > uc_src)
	{
		i = 0;
		while (i < len)
		{
			uc_dst[i] = uc_src[i];
			i++;
		}
	}
	else
		uc_dst = ft_memcpy(uc_dst, uc_src, len);
	return (dst);
}
