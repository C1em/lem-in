/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 18:19:50 by coremart          #+#    #+#             */
/*   Updated: 2019/09/15 06:51:38 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"
#include <stdlib.h>

static int	parse_graph(t_parser_graph *graph)
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

static int	treat_instructions(t_parser_graph *graph, char *line)
{
	if (line[1] != '#')
	{
		if (graph->parsing_list_start == NULL)
		{
			if (!(graph->parsing_list_start = init_pars_list(line)))
				return (set_msg(FAILURE, graph, MALLOC_ERROR));
			graph->parsing_list_end = graph->parsing_list_start;
		}
		else if (!(graph->parsing_list_end =
				add_pars_elem(graph->parsing_list_end, line)))
			return (set_msg(FAILURE, graph, MALLOC_ERROR));
	}
	return (SUCCESS);
}

static int	pars_ants_body(t_parser_graph *graph, char *line)
{
	int		i;

	i = 0;
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] != '\0')
		return (set_msg(FAILURE, graph, "Error : invalid position"));
	if (!ft_isint(line) || (graph->ants = ft_atoi(line)) < 0)
		return (set_msg(FAILURE, graph, "Error : wrong ant number"));
	if (graph->parsing_list_start == NULL)
	{
		if (!(graph->parsing_list_start = init_pars_list(line)))
			return (set_msg(FAILURE, graph, MALLOC_ERROR));
		graph->parsing_list_end = graph->parsing_list_start;
	}
	else if (!(graph->parsing_list_end =
			add_pars_elem(graph->parsing_list_end, line)))
		return (set_msg(FAILURE, graph, MALLOC_ERROR));
	return (SUCCESS);
}

static int	pars_ants(t_parser_graph *graph)
{
	char	*line;
	int		gnl_ret;

	while (graph->ants < 0)
	{
		if ((gnl_ret = get_next_line(STDIN, &line)) == -1)
			return (set_msg(FAILURE, graph, "Error : read"));
		else if (gnl_ret == 0)
			return (set_msg(FAILURE, graph, "Error : ants not set"));
		if (line[0] == '#')
		{
			if (treat_instructions(graph, line) == FAILURE)
				return (FAILURE);
		}
		else if (pars_ants_body(graph, line) == FAILURE)
			return (FAILURE);
		free(line);
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
