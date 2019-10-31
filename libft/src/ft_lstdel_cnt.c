/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_cnt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlamart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 16:52:08 by tlamart           #+#    #+#             */
/*   Updated: 2019/10/24 19:19:51 by tlamart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_cnt(void *content, size_t content_size)
{
	if (!content)
		return ;
	ft_bzero(content, content_size);
	ft_memdel(&content);
}
