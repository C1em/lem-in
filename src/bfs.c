/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:31:45 by cbenoit           #+#    #+#             */
/*   Updated: 2019/09/15 12:00:18 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

static int	bfs_body(t_graph *graph, int cur_vertex, int *next_vertex, int *i)
{
	if (graph->flow_arr[cur_vertex] == 2)
	{
		*next_vertex = get_incoming_flow_vertex(graph->adj_matrix, cur_vertex);
		*i = graph->adj_edges_arr[cur_vertex];
	}
	else
		*next_vertex = get_next_vertex(graph->adj_matrix[cur_vertex], *i);
	if (graph->level_arr[*next_vertex] == -1
	&& graph->adj_matrix[cur_vertex][*next_vertex] == NO_FLOW)
	{
		if (graph->flow_arr[*next_vertex] == 1 &&
		graph->adj_matrix[*next_vertex][cur_vertex] == NO_FLOW
		&& cur_vertex != graph->s_t.s)
			graph->flow_arr[*next_vertex] = 2;
		graph->level_arr[*next_vertex] = graph->level_arr[cur_vertex] + 1;
		return (1);
	}
	return (0);
}

int			bfs(t_graph *graph, t_parser_graph *p_graph)
{
	int			i;
	int			cur_vertex;
	int			next_vertex;
	t_queue_ptr	queue;

	ft_memset(graph->level_arr, -1, sizeof(int) * graph->size);
	graph->level_arr[graph->s_t.s] = 0;
	if (init_queue(&queue, graph->s_t.s) == FAILURE)
		return (set_msg(0, p_graph, MALLOC_ERROR));
	while (queue.start != NULL)
	{
		cur_vertex = dequeue(&queue);
		i = -1;
		while (++i < graph->adj_edges_arr[cur_vertex])
			if (bfs_body(graph, cur_vertex, &next_vertex, &i) == 1
			&& enqueue(&queue, next_vertex) == FAILURE)
				return (set_msg(0, p_graph, MALLOC_ERROR));
	}
	free_queue(&queue);
	return (graph->level_arr[graph->s_t.t] != -1);
}
