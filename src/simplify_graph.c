/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplify_graph.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 00:32:22 by coremart          #+#    #+#             */
/*   Updated: 2019/08/31 14:52:14 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "libft.h"
#include <stdlib.h>

void		simplify_graph(t_graph *graph, int s)
{
	int			i;
	int			tmp;
	t_queue_ptr	queue;
	t_edge		*edge;

	ft_memset(graph->level_arr, -1, sizeof(int) * graph->nb_vertices);
	graph->level_arr[s] = 0;
	init_queue(&queue, s);
	while (queue.start != NULL)
	{
		tmp = dequeue(&queue);
		i = 0;
		while (i < graph->adj_arr[tmp].nb_edges)
		{
			edge = &graph->edge_arr[graph->adj_arr[tmp].adj_index[i]];
			if (graph->level_arr[edge->to_vertex] < 0)
			{
				graph->level_arr[edge->to_vertex] = graph->level_arr[tmp] + 1;
				direct_edge(graph->edge_arr, graph->adj_arr[tmp].adj_index[i]);
				enqueue(&queue, edge->to_vertex);
			}
			else if (graph->level_arr[edge->to_vertex] == graph->level_arr[tmp] + 1)
				direct_edge(graph->edge_arr, graph->adj_arr[tmp].adj_index[i]);
			++i;
		}
	}
	free_queue(&queue);
}
