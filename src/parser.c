/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 18:19:50 by coremart          #+#    #+#             */
/*   Updated: 2019/09/11 16:39:42 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"
// #include "libft.h"
// #include <stdlib.h>

static int		parse_graph(t_parser_graph *graph)
{
	if (graph->ants <= 0)
		graph->msg = "Error : wrong ant number";
	else if (graph->commands.s < 0)
		graph->msg = "Error : room start not define";
	else if (graph->commands.t < 0)
		graph->msg = "Error : room end not define";
	else
		return (SUCCESS);
	return (FAILURE);
}

static int		pars_ants(t_parser_graph *graph)
{
	char	*line;
	int		gnl_ret;
	int		i;

	while (graph->ants < 0)
	{
		if ((gnl_ret = get_next_line(STDIN, &line)) == -1)
			return (set_msg(FAILURE, graph, "Error : read"));
		else if (gnl_ret == 0)
			return (set_msg(FAILURE, graph, "Error : ants not set"));
		if (line[0] == '#')
		{
			if (line[1] != '#')
			{
				if (graph->parsing_list_start == NULL)
				{
					if (!(graph->parsing_list_start = init_pars_list(line)))
						return (set_msg(FAILURE, graph, "Error : malloc"));
					graph->parsing_list_end = graph->parsing_list_start;
				}
				else if (!(graph->parsing_list_end = add_pars_elem(graph->parsing_list_end, line)))
					return (set_msg(FAILURE, graph, "Error : malloc"));
			}
		}
		else
		{
			i = 0;
			while (ft_isdigit(line[i]))
				i++;
			if (line[i] != '\0')
				return (set_msg(FAILURE, graph, "Error : invalid position"));
			if ((graph->ants = ft_atoi(line)) < 0)
				return (set_msg(FAILURE, graph, "Error : wrong ant number"));
			if (graph->parsing_list_start == NULL)
			{
				if (!(graph->parsing_list_start = init_pars_list(line)))
					return (set_msg(FAILURE, graph, "Error : malloc"));
				graph->parsing_list_end = graph->parsing_list_start;
			}
			else if (!(graph->parsing_list_end = add_pars_elem(graph->parsing_list_end, line)))
				return (set_msg(FAILURE, graph, "Error : malloc"));
		}
		free(line);
	}
	return (SUCCESS);
}

t_parser_graph	*init_pars_graph(void)
{
	t_parser_graph *graph;

	if (!(graph = (t_parser_graph*)malloc(sizeof(t_parser_graph)))
	|| !(graph->start = init_list()))
	{
		ft_putendl("Error");
		exit (0);
	}
	graph->end = graph->start;
	graph->parsing_list_end = NULL;
	graph->parsing_list_start = NULL;
	graph->commands.s = -1;
	graph->commands.t = -1;
	graph->ants = -1;
	graph->msg = "OK";
	graph->nb_lines = 0;
	return (graph);
}

static int			init_pars_arrays(t_parser_graph *p_graph)
{
	int		size;

	if ((size = p_graph->end->vertex.nb) <= 0)
		return (set_msg(FAILURE, p_graph, "Error : no room set")); //<- Verify error msg
	if (!(p_graph->matrix = (int**)malloc(sizeof(int*) * size)))
		return (set_msg(FAILURE, p_graph, "Error : malloc"));
	if (!(p_graph->adj_edges_count = (int*)malloc(sizeof(int) * size)))
		return (set_msg(FAILURE, p_graph, "Error : malloc"));
	ft_bzero(p_graph->adj_edges_count, sizeof(int) * size);
	while (size--)
	{
		if (!(p_graph->matrix[size] = (int*)malloc(sizeof(int) * p_graph->end->vertex.nb)))
			return (set_msg(FAILURE, p_graph, "Error : malloc"));
		ft_bzero(p_graph->matrix[size], sizeof(int) * p_graph->end->vertex.nb);
	}
	return (SUCCESS);
}

int			parser(t_parser_graph *graph)
{
	char			*line_tmp;

	if (pars_ants(graph) == FAILURE)
		return (FAILURE);
	if (!(line_tmp = pars_vertices(graph)))
		return (FAILURE);
	if (init_pars_arrays(graph) == FAILURE)
		return (FAILURE);
	if (pars_edges(graph, line_tmp) == FAILURE)
		return (FAILURE);
	if (parse_graph(graph) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
