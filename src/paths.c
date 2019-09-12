/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 19:23:57 by coremart          #+#    #+#             */
/*   Updated: 2019/09/12 11:15:27 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"
// #include <stdlib.h>
// #include <stdio.h>

static t_path	get_path(t_graph *graph, int cur_vertex)
{
	int		i;
	int		next_vertex;
	t_path	path;

	if (!(path.path = (int*)malloc(sizeof(int) * graph->size)))
		return ((t_path){NULL, 0, 0});
	path.len = 0;
	while (cur_vertex != graph->s_t.t)
	{
		i = 0;
		path.path[path.len] = cur_vertex;
		path.len++;
		while (i < graph->adj_edges_arr[cur_vertex]
		&& graph->adj_matrix[cur_vertex]
		[(next_vertex = get_next_vertex(graph->adj_matrix[cur_vertex], i))]
		== NO_FLOW)
			i++;
	//	printf("cur vertex :%d\n", cur_vertex);
		cur_vertex = next_vertex;
	}
	return (path);
}

t_paths	get_new_paths(t_graph *graph, int size)
{
	t_paths	paths;
	int		i;
	int		j;
	int		next_vertex;

	if (!(paths.paths = (t_path*)malloc(sizeof(t_path) * size)))
		return ((t_paths){NULL, 0});
	paths.size = size;
	i = 0;
	j = 0;
	while (i < graph->adj_edges_arr[graph->s_t.s])
	{
		if (graph->adj_matrix[graph->s_t.s]
		[(next_vertex = get_next_vertex(graph->adj_matrix[graph->s_t.s], i))] == FLOW)
		{
//			printf("WAW !!! next vertex : %d\n", next_vertex);
			if (!(paths.paths[j] = get_path(graph, next_vertex)).path)
			{
				//free paths.paths
				return ((t_paths){NULL, 0});
			}
			++j;
		}
		++i;
	}
	q_sort_paths(paths);
//	printf("path len :%d\n", paths.paths[0].len);
	return (paths);
}


void	dispatch_ants(t_paths paths, const int ants)
{
	int	i;
	int	remainder;
	int	ants_tmp;

	if (paths.size == 0)
		return ;
	if (paths.paths[0].len == 0)
	{
		paths.paths[0].ants_on = ants;
		return ;
	}
	i = 0;
	ants_tmp = ants;
	while (++i < paths.size)
	{
		if ((ants_tmp -= (paths.paths[i].len - paths.paths[i - 1].len) * i) < paths.size)
		{
			// free the paths from i + 1 to paths.size - 1 ????
			paths.size = i;
			return (dispatch_ants(paths, ants));
		}
	}
	remainder = ants_tmp % paths.size;
	ants_tmp /= paths.size;
	while (--i)
	{
		paths.paths[i].ants_on = ants_tmp;
		ants_tmp += paths.paths[i].len - paths.paths[i - 1].len;
	}
	paths.paths[i].ants_on = ants_tmp;
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
	if (cur_paths.paths[0].len == 0)
		return (1);
//	printf("cur op :%d, new op :%d\n", cur_paths.paths[0].len + cur_paths.paths[0].ants_on, new_paths.paths[0].len + new_paths.paths[0].ants_on);
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
