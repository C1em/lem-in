/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 00:21:32 by coremart          #+#    #+#             */
/*   Updated: 2019/03/08 02:26:02 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_memswap(void *s1, void *s2, size_t size)
{
	void *tmp;

	tmp = ft_memdup(s1, size);
	s1 = ft_memcpy(s1, s2, size);
	s2 = ft_memcpy(s2, tmp, size);
	free(tmp);
}
