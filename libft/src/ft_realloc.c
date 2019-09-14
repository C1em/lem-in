/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 19:29:54 by coremart          #+#    #+#             */
/*   Updated: 2019/06/25 19:40:14 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_realloc(void *ptr, size_t initial_size, size_t final_size)
{
	void	*res;

	if (!ptr || final_size <= 0 || !(res = malloc(final_size)))
		return (NULL);
	res = ft_memcpy(res, ptr, initial_size);
	free(ptr);
	return (res);
}
