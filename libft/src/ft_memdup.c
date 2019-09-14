/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 09:58:08 by coremart          #+#    #+#             */
/*   Updated: 2018/11/16 13:46:10 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memdup(const void *src, size_t size)
{
	void	*dst;

	if (!(dst = malloc(sizeof(unsigned char) * size)))
		return (NULL);
	ft_memcpy(dst, src, size);
	return (dst);
}
