/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 17:13:16 by coremart          #+#    #+#             */
/*   Updated: 2018/11/16 13:45:38 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (0);
	while (*((unsigned char*)s1 + i) == *((unsigned char*)s2 + i) && i < n - 1)
		i++;
	return (*((unsigned char*)s1 + i) - *((unsigned char*)s2 + i));
}
