/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_flow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 15:35:09 by coremart          #+#    #+#             */
/*   Updated: 2019/09/03 23:08:17 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "libft.h"
#include <stdlib.h>

#include <stdio.h>

/*
**	construct the level graph, a edge is'nt considered part of the graph if
**	it's at its max flow.
**
**	return 1 if t i reached else return 0.
*/
static int	bfs(t_graph *graph, int s, int t)
{
	int			i;
	int			tmp;
	t_queue_ptr	queue;
	t_edge		*edge;

	ft_memset(graph->level_arr, -1, sizeof(int) * graph->nb_vertices);
	graph->level_arr[s] = 0;
	init_queue(&queue, s);
	enqueue(&queue, s);
	while (queue.start != NULL)
	{
		tmp = dequeue(&queue);
		i = 0;
		while (i < graph->adj_arr[tmp].nb_edges)
		{
			edge = &graph->edge_arr[graph->adj_arr[tmp].adj_index[i]];
			// If the edge has still no level and it can has more flow,
			// put its level in level's array and enqueue
			if (graph->level_arr[edge->to_vertex] < 0 && edge->flow < edge->capacity)
			{
				graph->level_arr[edge->to_vertex] = graph->level_arr[tmp] + 1;
				enqueue(&queue, edge->to_vertex);
			}
			++i;
		}
	}
	free_queue(&queue);
	return (graph->level_arr[t] != -1);
}

// cur_flow always equal to 1 ???????
// return 0 if cur_flow == 0 ???????
// rm edge_index
static int	dfs(t_graph *graph, int cur_vertex, int cur_flow, int t, int *visited)
{
	int		edge_index;
	t_edge	*edge;

	if (cur_vertex == t && printf("end !!!\n"))
		return (cur_flow);
	if (cur_vertex >= graph->nb_vertices >> 1)
		printf("vertex :%d out\n", graph->nb_vertices - cur_vertex - 1);
	else
		printf("vertex :%d in\n", cur_vertex);
	while (visited[cur_vertex] < graph->adj_arr[cur_vertex].nb_edges)
	{
		edge_index = graph->adj_arr[cur_vertex].adj_index[visited[cur_vertex]];
		edge = &graph->edge_arr[edge_index];
		if (edge->to_vertex >= graph->nb_vertices >> 1)
			printf("\tedge :%d out\n", graph->nb_vertices - edge->to_vertex - 1);
		else
			printf("\tedge :%d in\n", edge->to_vertex);
		if (graph->level_arr[edge->to_vertex] == graph->level_arr[cur_vertex] + 1
			&& edge->flow < edge->capacity)
			if (dfs(graph, edge->to_vertex, edge->capacity - edge->flow, t, visited))
			{
				--graph->edge_arr[edge_index ^ 1].flow;
				return ((edge->flow = 1));
			}
		visited[cur_vertex]++;
	}
	printf("bad path !!\n");
	return (0);
}

/*
**	custom Dinic's algo
*/
t_paths		get_max_flow(t_graph *graph, int s, int t, int ants)
{
	int		flow;
	int		max_flow;
	int		*visited;
	t_paths	current_paths;
	t_paths	new_paths;


	if (s == t)
		return ((t_paths){NULL, 0});
	max_flow = 0;
	current_paths = (t_paths){NULL, 0};
	if (!(visited = (int*)malloc(graph->nb_vertices * sizeof(int))))
		exit(1);
	while (bfs(graph, s, t) && printf("still a path !\n"))
	{
		ft_bzero(visited, sizeof(int) * graph->nb_vertices);
		while ((flow = dfs(graph, s, INF, t, visited)))
			max_flow += flow;
		new_paths = get_new_paths(graph, max_flow, s, t);
		dispatch_ants(new_paths, ants);
		if (is_worse_path(current_paths, new_paths) && printf("\nStop, best paths found\n\n"))
			break;
		free_paths(current_paths);
		current_paths = new_paths;
	}
	return (current_paths);
}
