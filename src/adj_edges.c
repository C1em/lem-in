/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adj_edges.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 13:20:30 by coremart          #+#    #+#             */
/*   Updated: 2019/09/04 19:16:17 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "libft.h"
#include <stdlib.h>

void	init_adj_edges(t_adj_edges *adj_edges)
{
	adj_edges->size_arr = SIZE_ARR;
	if (!(adj_edges->adj_index = (unsigned int*)malloc(SIZE_ARR * sizeof(unsigned int))))
		exit(1);
	adj_edges->nb_edges = 0;
}

void	push_back_adj_edges(t_adj_edges *adj_edges, unsigned int index_of_edge)
{
	if (adj_edges->nb_edges == adj_edges->size_arr)
	{
		adj_edges->adj_index = (unsigned int*)ft_realloc(adj_edges->adj_index,
								adj_edges->size_arr * sizeof(unsigned int),
								(adj_edges->size_arr + SIZE_ARR) * sizeof(unsigned int));
		adj_edges->size_arr += 100;
	}
	adj_edges->adj_index[adj_edges->nb_edges] = index_of_edge;
	++adj_edges->nb_edges;
}

void	rm_adj_edge(t_graph *graph, t_adj_edges *adj_edge, unsigned int to)
{
	unsigned int	i;

	i = 0;
	while (graph->edge_arr[adj_edge->adj_index[i]].to_vertex != to)
		++i;
	ft_memmove(&adj_edge->adj_index[i], &adj_edge->adj_index[i + 1],
				sizeof(unsigned int) * (--adj_edge->nb_edges - i));
}
