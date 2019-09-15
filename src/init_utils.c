/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 17:21:12 by cbenoit           #+#    #+#             */
/*   Updated: 2019/09/15 13:51:28 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"
#include <stdlib.h>

t_parser_graph	*init_pars_graph(void)
{
	t_parser_graph *graph;

	if (!(graph = (t_parser_graph*)malloc(sizeof(t_parser_graph)))
	|| !(graph->start = init_list()))
	{
		ft_putendl("Error");
		exit(EXIT_FAILURE);
	}
	graph->end = graph->start;
	graph->parsing_list_end = NULL;
	graph->parsing_list_start = NULL;
	graph->commands.s = -1;
	graph->commands.t = -1;
	graph->ants = -1;
	graph->msg = "OK";
	graph->nb_lines = 0;
	graph->ants_on_rooms = 0;
	graph->ants_at_end = 0;
	graph->adj_edges_count = NULL;
	graph->matrix = NULL;
	return (graph);
}

int				init_pars_arrays(t_parser_graph *p_graph)
{
	int		size;

	if ((size = p_graph->end->vertex.nb) <= 0)
		return (set_msg(FAILURE, p_graph, "Error : room_parser"));
	if (!(p_graph->matrix = (int**)malloc(sizeof(int*) * size)))
		return (set_msg(FAILURE, p_graph, MALLOC_ERROR));
	if (!(p_graph->adj_edges_count = (int*)malloc(sizeof(int) * size)))
		return (set_msg(FAILURE, p_graph, MALLOC_ERROR));
	ft_bzero(p_graph->adj_edges_count, sizeof(int) * size);
	while (size--)
	{
		if (!(p_graph->matrix[size] =
		(int*)malloc(sizeof(int) * p_graph->end->vertex.nb)))
			return (set_msg(FAILURE, p_graph, MALLOC_ERROR));
		ft_bzero(p_graph->matrix[size], sizeof(int) * p_graph->end->vertex.nb);
	}
	return (SUCCESS);
}
