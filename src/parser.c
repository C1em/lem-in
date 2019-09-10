/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 18:19:50 by coremart          #+#    #+#             */
/*   Updated: 2019/09/10 16:34:49 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"
// #include "libft.h"
// #include <stdlib.h>

void			pars_ants(t_parser_graph *graph)
{
	char	*line;
	int		gnl_ret;
	int		i;

	while (graph->ants < 0)
	{
		if ((gnl_ret = get_next_line(STDIN, &line)) == -1)
			error_sys();
		else if (gnl_ret == 0)
			error_input();
		if (line[0] == '#')
		{
			if (line[1] != '#')
			{
				if (graph->parsing_list_start == NULL)
				{
					graph->parsing_list_start = init_pars_list(line);
					graph->parsing_list_end = graph->parsing_list_start;
				}
				else
					graph->parsing_list_end = add_pars_elem(graph->parsing_list_end, line);
			}
		}
		else
		{
			i = 0;
			while (ft_isdigit(line[i]))
				i++;
			if (line[i] != '\0')
				error_input();
			if ((graph->ants = ft_atoi(line)) < 0)
				error_input();
			if (graph->parsing_list_start == NULL)
			{
				graph->parsing_list_start = init_pars_list(line);
				graph->parsing_list_end = graph->parsing_list_start;
			}
			else
				graph->parsing_list_end = add_pars_elem(graph->parsing_list_end, line);
		}
		free(line);
	}
}

t_parser_graph	*init_pars_graph(void)
{
	t_parser_graph *graph;

	if (!(graph = (t_parser_graph*)malloc(sizeof(t_parser_graph))))
		error_sys();
	graph->start = init_list();
	graph->end = graph->start;
	graph->parsing_list_end = NULL;
	graph->parsing_list_start = NULL;
	graph->commands.s = -1;
	graph->commands.t = -1;
	graph->ants = -1;
	return (graph);
}

void			init_pars_arrays(t_parser_graph *p_graph)
{
	int		size;

	if ((size = p_graph->end->vertex.nb) <= 0)
		error_input();
	if (!(p_graph->matrix = (int**)malloc(sizeof(int*) * size)))
		error_sys();
	if (!(p_graph->adj_edges_count = (int*)malloc(sizeof(int) * size)))
		error_sys();
	ft_bzero(p_graph->adj_edges_count, sizeof(int) * size);
	while (size--)
	{
		if (!(p_graph->matrix[size] = (int*)malloc(sizeof(int) * p_graph->end->vertex.nb)))
			error_sys();
		ft_bzero(p_graph->matrix[size], sizeof(int) * p_graph->end->vertex.nb);
	}
}

t_parser_graph	*parser(void)
{
	t_parser_graph	*graph;
	char			*line_tmp;

	graph = init_pars_graph();
	pars_ants(graph);
	line_tmp = pars_vertices(graph);
	init_pars_arrays(graph);
	pars_edges(graph, line_tmp);
	return (graph);
}
