/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q_sort_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 21:46:51 by coremart          #+#    #+#             */
/*   Updated: 2019/09/15 06:54:32 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

static void	qsort_paths(t_path paths[], int end)
{
	unsigned int	swapable;
	unsigned int	i;
	t_path			tmp;

	if (end == -1)
		return ;
	swapable = 0;
	i = 0;
	while (i < (unsigned int)end)
	{
		if (paths[i].len < paths[end].len)
		{
			tmp = paths[i];
			paths[i] = paths[swapable];
			paths[swapable] = tmp;
			++swapable;
		}
		++i;
	}
	tmp = paths[i];
	paths[i] = paths[swapable];
	paths[swapable] = tmp;
	qsort_paths(paths, swapable - 1);
	if (swapable + 1 < (unsigned int)end)
		qsort_paths(&paths[swapable + 1], end - swapable - 1);
}

void		q_sort_paths(t_paths paths)
{
	return (qsort_paths(paths.paths, paths.size - 1));
}
