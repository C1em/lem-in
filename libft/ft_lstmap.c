/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 16:40:06 by coremart          #+#    #+#             */
/*   Updated: 2018/11/16 13:44:45 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *res;
	t_list *tmp;

	if (!(lst && f))
		return (NULL);
	if (!(res = ft_lstnew((f(lst))->content, (f(lst))->content_size)))
		return (NULL);
	tmp = res;
	lst = lst->next;
	while (lst)
	{
		if (!(tmp->next = ft_lstnew((f(lst))->content, (f(lst))->content_size)))
			return (NULL);
		tmp = tmp->next;
		lst = lst->next;
	}
	tmp->next = NULL;
	return (res);
}
