/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_flow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 15:35:09 by coremart          #+#    #+#             */
/*   Updated: 2019/09/15 06:47:16 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"
#include <stdlib.h>

int			get_next_vertex(int *vertex_arr, int index)
{
	int i;

	i = 0;
	while (1)
	{
		if (vertex_arr[i] & EDGE)
			if (index-- == 0)
				return (i);
		i++;
	}
	return (i);
}

int			get_incoming_flow_vertex(int **matrix, int vertex)
{
	int	i;

	i = 0;
	while (matrix[i][vertex] != FLOW)
		i++;
	return (i);
}

static int	get_max_flow_setup(t_parser_graph *p_graph, t_graph *graph,
					t_paths *current_paths, int **visited)
{
	*current_paths = (t_paths){NULL, 0};
	if (graph->s_t.s == graph->s_t.t)
		p_graph->msg = "Error : start and end have the same index";
	else if (!(*visited = (int*)malloc(graph->size * sizeof(int))))
		p_graph->msg = MALLOC_ERROR;
	else
		return (SUCCESS);
	return (FAILURE);
}

static int	get_max_flow_body(t_graph *graph, t_paths *current_paths,
			t_paths new_paths)
{
	dispatch_ants(&new_paths, graph->ants);
	if (is_worse_path(*current_paths, new_paths))
	{
		free_paths(new_paths);
		return (1);
	}
	free_paths(*current_paths);
	*current_paths = new_paths;
	return (0);
}

t_paths		get_max_flow(t_parser_graph *p_graph, t_graph *graph)
{
	int		max_flow;
	int		*visited;
	t_paths	current_paths;
	t_paths	new_paths;

	if (get_max_flow_setup(p_graph, graph, &current_paths, &visited) == FAILURE)
		return (current_paths);
	max_flow = 0;
	while (bfs(graph, p_graph))
	{
		ft_bzero(visited, sizeof(int) * graph->size);
		if (dfs(graph, graph->s_t.s, visited))
			max_flow++;
		if (!(new_paths = get_new_paths(graph, max_flow)).paths)
		{
			free_paths(current_paths);
			free(visited);
			return (new_paths);
		}
		if (get_max_flow_body(graph, &current_paths, new_paths) == 1)
			break ;
	}
	free(visited);
	return (current_paths);
}
