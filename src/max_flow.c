/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_flow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 15:35:09 by coremart          #+#    #+#             */
/*   Updated: 2019/09/08 05:54:23 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
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
	init_queue(&queue, graph->s_t.s);
	while (queue.start != NULL)
	{
		cur_vertex = dequeue(&queue);
		i = -1;
		while (++i < graph->adj_edges_arr[cur_vertex])
		{
			next_vertex = get_next_vertex(graph->adj_matrix[cur_vertex], i);
			// If the edge has still no level and it can has more flow,
			// put its level in level's array and enqueue
			if (graph->level_arr[next_vertex] == -1
//			&& printf("no level\n")
			&& graph->adj_matrix[cur_vertex][next_vertex] == NO_FLOW)
//			&& printf("no flow\n"))
			{
/*				printf("i :%d\n", i);
				printf("cur vertex :%d\n", cur_vertex);
				printf("next vertex :%d\n", next_vertex);
*/				if (graph->flow_arr[cur_vertex] == 2)
				{
//					printf("start climbing the flow\n");
					next_vertex = get_incoming_flow_vertex(graph->adj_matrix, cur_vertex);
					graph->level_arr[next_vertex] = graph->level_arr[cur_vertex] + 1;
					enqueue(&queue, next_vertex);
//					printf("incoming flow vertex :%d\n", next_vertex);
					break ;
				}
				if (graph->flow_arr[cur_vertex] == 0 && graph->flow_arr[next_vertex] == 1 && cur_vertex != graph->s_t.s)
					graph->flow_arr[next_vertex] = 2;
				graph->level_arr[next_vertex] = graph->level_arr[cur_vertex] + 1;
				enqueue(&queue, next_vertex);
			}
		}
	}
	free_queue(&queue);
//	printf("level of %d : %d\n",graph->s_t.t, graph->level_arr[graph->s_t.t]);
	return (graph->level_arr[graph->s_t.t] != -1);
}

static int	dfs(t_graph *graph, int cur_vertex, int *visited)
{
	int		next_vertex;

	if (cur_vertex == graph->s_t.t && printf("good path !!\n"))
		return (1);
	while (visited[cur_vertex] < graph->adj_edges_arr[cur_vertex])
	{
		next_vertex = get_next_vertex(graph->adj_matrix[cur_vertex], visited[cur_vertex]);
		printf("vertex :%d\n", cur_vertex);
		if (graph->level_arr[next_vertex] == graph->level_arr[cur_vertex] + 1
		&& graph->adj_matrix[cur_vertex][next_vertex] == NO_FLOW)
		{
			printf("\tedge :%d\n", next_vertex);
			if (graph->flow_arr[cur_vertex] == 2)
			{
				printf("%d is the blocking vertex\n", cur_vertex);
				graph->flow_arr[cur_vertex] = 1;
				next_vertex = get_incoming_flow_vertex(graph->adj_matrix, cur_vertex);
				visited[cur_vertex] += graph->adj_edges_arr[cur_vertex];
			}
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
					graph->flow_arr[next_vertex] = 0;
					graph->adj_matrix[next_vertex][cur_vertex] = NO_FLOW;
				}
				return (1);
			}
		}
		visited[cur_vertex]++;
	}
	printf("bad path !!\n");
	return (0);
}

/*
**	custom Dinic's algo
*/
t_paths				get_max_flow(t_graph *graph)
{
	int		flow;
	int		max_flow;
	int		*visited;
	t_paths	current_paths;
	t_paths	new_paths;

	if (graph->s_t.s == graph->s_t.t)
		return ((t_paths){NULL, 0});
	max_flow = 0;
	current_paths = (t_paths){NULL, 0};
	if (!(visited = (int*)malloc(graph->size * sizeof(int))))
		exit(1);
	while (bfs(graph)/* && printf("still a path !\n")*/)
	{
		ft_bzero(visited, sizeof(int) * graph->size);
		while ((flow = dfs(graph, graph->s_t.s, visited)))
			max_flow += flow;
/*		if (flow == 0)
			exit(1);
*/		new_paths = get_new_paths(graph, max_flow);
		dispatch_ants(new_paths, graph->ants);
		if (is_worse_path(current_paths, new_paths) && printf("\nStop, best paths found\n\n"))
			break;
		free_paths(current_paths);
		current_paths = new_paths;
	}
	return (current_paths);
}
