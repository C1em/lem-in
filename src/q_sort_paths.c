/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q_sort_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 21:46:51 by coremart          #+#    #+#             */
/*   Updated: 2019/09/04 15:45:08 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void		qsort_paths(t_path paths[], int start, int end)
{
	int		swapable;
	int		i;
	t_path	tmp;

	if(start >= end)
		return ;
	swapable = start;
	i = start;
	while (i < end)
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
	qsort_paths(paths, start, swapable - 1);
	qsort_paths(paths, swapable + 1, end);
}

void		q_sort_paths(t_paths paths)
{
	return (qsort_paths(paths.paths, 0, paths.size - 1));
}
