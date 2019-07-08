/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 17:35:54 by coremart          #+#    #+#             */
/*   Updated: 2018/11/16 14:01:28 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstdup(t_list *src)
{
	t_list *dst;
	t_list *tmp;

	if (!(src))
		return (NULL);
	if (!(dst = ft_lstnew(src->content, src->content_size)))
		return (NULL);
	tmp = dst;
	src = src->next;
	while (src)
	{
		if (!(tmp->next = ft_lstnew(src->content, src->content_size)))
			return (NULL);
		tmp = tmp->next;
		src = src->next;
	}
	tmp = NULL;
	return (dst);
}
