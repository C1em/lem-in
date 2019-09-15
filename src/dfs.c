/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:44:39 by cbenoit           #+#    #+#             */
/*   Updated: 2019/09/15 11:54:37 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		dfs_body(t_graph *graph, int cur_vertex, int next_vertex)
{
	if (graph->adj_matrix[next_vertex][cur_vertex] == NO_FLOW)
	{
		graph->adj_matrix[cur_vertex][next_vertex] = FLOW;
		if (next_vertex != graph->s_t.t)
			graph->flow_arr[next_vertex] = 1;
		if (cur_vertex != graph->s_t.s)
			graph->flow_arr[cur_vertex] = 1;
	}
	else
	{
		graph->flow_arr[cur_vertex] = 0;
		graph->adj_matrix[next_vertex][cur_vertex] = NO_FLOW;
	}
	return (1);
}

int				dfs(t_graph *graph, int cur_vertex, int *visited)
{
	int		next_vertex;

	if (cur_vertex == graph->s_t.t)
		return (1);
	while (visited[cur_vertex] < graph->adj_edges_arr[cur_vertex])
	{
		if (graph->flow_arr[cur_vertex] == 2)
		{
			graph->flow_arr[cur_vertex] = 1;
			next_vertex =
			get_incoming_flow_vertex(graph->adj_matrix, cur_vertex);
			visited[cur_vertex] = graph->adj_edges_arr[cur_vertex];
		}
		else
			next_vertex =
			get_next_vertex(graph->adj_matrix[cur_vertex], visited[cur_vertex]);
		if (graph->level_arr[next_vertex] == graph->level_arr[cur_vertex] + 1
		&& graph->adj_matrix[cur_vertex][next_vertex] == NO_FLOW)
			if (dfs(graph, next_vertex, visited))
				return (dfs_body(graph, cur_vertex, next_vertex));
		visited[cur_vertex]++;
	}
	return (0);
}
