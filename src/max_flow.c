/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_flow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 15:35:09 by coremart          #+#    #+#             */
/*   Updated: 2019/09/13 14:56:13 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

int				get_next_vertex(int *vertex_arr, int index)
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

static int			get_incoming_flow_vertex(int **matrix, int vertex)
{
	int	i;

	i = 0;
	while (matrix[i][vertex] != FLOW)
		i++;
	return (i);
}

/*
**	construct the level graph, a edge is'nt considered part of the graph if
**	it's at its max flow.
**
**	return 1 if t i reached else return 0.
*/
static int			bfs(t_graph *graph)
{
	int			i;
	int			cur_vertex;
	int			next_vertex;
	t_queue_ptr	queue;

	ft_memset(graph->level_arr, -1, sizeof(int) * graph->size);
	graph->level_arr[graph->s_t.s] = 0;
	init_queue(&queue, graph->s_t.s); //<- gerer valeur retour if == failure -> sortir du bfs et retourner au main
	while (queue.start != NULL)
	{
		cur_vertex = dequeue(&queue);
		i = -1;
		while (++i < graph->adj_edges_arr[cur_vertex])
		{
			if (graph->flow_arr[cur_vertex] == 2)
			{
				next_vertex = get_incoming_flow_vertex(graph->adj_matrix, cur_vertex);
				i = graph->adj_edges_arr[cur_vertex];
			}
			else
				next_vertex = get_next_vertex(graph->adj_matrix[cur_vertex], i);
			if (graph->level_arr[next_vertex] == -1
			&& graph->adj_matrix[cur_vertex][next_vertex] == NO_FLOW)
			{
				if (graph->flow_arr[next_vertex] == 1 && graph->adj_matrix[next_vertex][cur_vertex] == NO_FLOW && cur_vertex != graph->s_t.s)
					graph->flow_arr[next_vertex] = 2;
				graph->level_arr[next_vertex] = graph->level_arr[cur_vertex] + 1;
				enqueue(&queue, next_vertex); // idem gerer valeur retour if == failure -> sortir du bfs et retourner au main
			}
		}
	}
	free_queue(&queue);
	return (graph->level_arr[graph->s_t.t] != -1);
}

static int	dfs(t_graph *graph, int cur_vertex, int *visited)
{
	int		next_vertex;

	if (cur_vertex == graph->s_t.t)
		return (1);
	while (visited[cur_vertex] < graph->adj_edges_arr[cur_vertex])
	{
		if (graph->flow_arr[cur_vertex] == 2)
		{
			graph->flow_arr[cur_vertex] = 1;
			next_vertex = get_incoming_flow_vertex(graph->adj_matrix, cur_vertex);
			visited[cur_vertex] = graph->adj_edges_arr[cur_vertex];
		}
		else
			next_vertex = get_next_vertex(graph->adj_matrix[cur_vertex], visited[cur_vertex]);
		if (graph->level_arr[next_vertex] == graph->level_arr[cur_vertex] + 1
		&& graph->adj_matrix[cur_vertex][next_vertex] == NO_FLOW)
		{
			if (dfs(graph, next_vertex, visited))
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
		}
		visited[cur_vertex]++;
	}
//	printf("bad path !!\n");
	return (0);
}

/*
**	custom Dinic's algo
*/
t_paths				get_max_flow(t_parser_graph *p_graph, t_graph *graph)
{
	int		max_flow;
	int		*visited;
	t_paths	current_paths;
	t_paths	new_paths;

	if (graph->s_t.s == graph->s_t.t)
		return ((t_paths){NULL, 0});
	max_flow = 0;
	current_paths = (t_paths){NULL, 0};
	if (!(visited = (int*)malloc(graph->size * sizeof(int))))
	{
		p_graph->msg = MALLOC_ERROR;
		return (current_paths);
	}
	while (bfs(graph))
	{
		ft_bzero(visited, sizeof(int) * graph->size);
		while (dfs(graph, graph->s_t.s, visited))
			max_flow++;
		if (!(new_paths = get_new_paths(graph, max_flow)).paths)
		{
			free_paths(current_paths);
			free(visited);
			return (new_paths);
		}
		dispatch_ants(new_paths, graph->ants);
		if (is_worse_path(current_paths, new_paths))
		{
			free_paths(new_paths);
			break;
		}
		free_paths(current_paths);
		current_paths = new_paths;
	}
	free(visited);
	return (current_paths);
}
