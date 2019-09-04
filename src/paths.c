/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 19:23:57 by coremart          #+#    #+#             */
/*   Updated: 2019/09/04 19:43:16 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lem-in.h"

#include <stdio.h>

t_path	get_path(t_graph *graph, t_edge *edge, unsigned int t)
{
	unsigned int	cur_vertex;
	unsigned int	i;
	unsigned int	j;
	t_path			path;

	cur_vertex = edge->to_vertex;
	j = 0;
	if (!(path.path = (unsigned int*)malloc(sizeof(unsigned int) * graph->nb_vertices)))
		exit(1);
	while (cur_vertex != t)
	{
		i = 0;
		if (cur_vertex < graph->nb_vertices >> 1)
		{
			path.path[j] = cur_vertex;
			++j;
		}
		while (graph->edge_arr[graph->adj_arr[cur_vertex].adj_index[i]].flow == 0)
			i++;
		cur_vertex = graph->edge_arr[graph->adj_arr[cur_vertex].adj_index[i]].to_vertex;
	}
	path.len = j;
	return (path);
}

t_paths	get_new_paths(t_graph *graph, unsigned int size, unsigned int s, unsigned int t)
{
	t_edge			*edge;
	t_paths			paths;
	unsigned int	i;
	unsigned int	j;

	if (!(paths.paths = (t_path*)malloc(sizeof(t_path) * size)))
		exit(1);
	paths.size = size;
	i = 0;
	j = 0;
	while (i < graph->adj_arr[s].nb_edges)
	{
		edge = &graph->edge_arr[graph->adj_arr[s].adj_index[i]];
		if (edge->flow == 1)
		{
			paths.paths[j] = get_path(graph, edge, t);
			++j;
		}
		++i;
	}
	q_sort_paths(paths);
	return (paths);
}


void	dispatch_ants(t_paths paths, unsigned int ants)
{
	unsigned int	i;
	unsigned int	remainder;

	if (paths.size == 0)
		return ;
	i = 0;
	printf("paths size : %d\n", paths.size);
	while (++i < paths.size)
	{
		if (ants <= (paths.paths[i].len - paths.paths[i - 1].len) * i)
		{
			paths.size = i;
			return (dispatch_ants(paths, ants));
		}
		else
			 ants -= (paths.paths[i].len - paths.paths[i - 1].len) * i;

	}
	remainder = ants % paths.size;
	ants /= paths.size;
	while (--i)
	{
		paths.paths[i].ants_on = ants;
		ants += paths.paths[i].len - paths.paths[i - 1].len;
	}
	paths.paths[i].ants_on = ants;
	while (remainder--)
	{
		++paths.paths[i].ants_on;
		++i;
	}
}

int		is_worse_path(t_paths cur_paths,t_paths new_paths)
{
	if (cur_paths.paths == NULL)
		return (0);
	if (cur_paths.paths[0].len + cur_paths.paths[0].ants_on
	<= new_paths.paths[0].len + new_paths.paths[0].ants_on)
		return (1);
	return  (0);
}

void	free_paths(t_paths paths)
{
	if (paths.paths == NULL)
		return ;
	while (paths.size--)
		free(paths.paths[paths.size].path);
	free(paths.paths);
}
