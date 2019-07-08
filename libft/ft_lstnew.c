/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 09:44:31 by coremart          #+#    #+#             */
/*   Updated: 2018/11/16 13:44:55 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*res;

	if (!(res = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (!(content))
	{
		res->content = NULL;
		res->content_size = 0;
	}
	else
	{
		if (!(res->content = ft_memdup((const void*)content, content_size)))
			return (NULL);
		res->content_size = content_size;
	}
	res->next = NULL;
	return (res);
}
