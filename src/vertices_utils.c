/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertices_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 21:57:19 by coremart          #+#    #+#             */
/*   Updated: 2019/09/12 11:08:17 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"
// #include "libft.h"
// #include <stdlib.h>

static int				add_command(char line[])
{
	int	i;

	i = 0;
	while (i < 2 && ft_strcmp(line, (((char*[2]){"start", "end"})[i])) != SAME)
		i++;
	return (i);
}

char				*pars_name(char *line)
{
	int i;
	int j;

	i = 0;
	while (line[i] && line[i] != ' ')
		if (line[i++] == '-')
			return (NULL);
	if (line[i] == '\0')
		return (NULL);
	j = i + 1;
	while (ft_isdigit(line[j]))
		j++;
	if (line[j] != ' ' || !ft_isdigit(line[j - 1]))
		return (NULL);
	j++;
	while (ft_isdigit(line[j]))
		j++;
	if (line[j] != '\0' || !ft_isdigit(line[j - 1]))
		return (NULL);
	return (ft_strndup(line, i));
}

static int				add_vertex(char line[], t_parser_graph *graph, int *command_nb)
{
	if (graph->start->vertex.name == NULL)
		graph->start->vertex.name = pars_name(line);
	else if (add_elem(&graph->end, line) == FAILURE)
	{
		free(line);
		line = NULL;
		return (set_msg(FAILURE, graph, MALLOC_ERROR));
	}
	if (graph->end->vertex.name == NULL)
		return (0);
	if (check_vertex_dup(graph->start, graph->end->vertex.name))
	{
		free(graph->end->vertex.name);
		graph->end->vertex.name = NULL;
		return (0);
	}
	if (*command_nb == 0)
		graph->commands.s = graph->end->vertex.nb;
	else if (*command_nb == 1)
		graph->commands.t = graph->end->vertex.nb;
	*command_nb = 2;
	return (1);
}

int				get_vertex(char *str, t_vertex_list *start)
{

	while (start->vertex.name && ft_strcmp(start->vertex.name, str) != SAME)
		start = start->next;
	if (start->vertex.name == NULL)
		return (-1);
	return (start->vertex.nb);

}

char		*pars_vertices(t_parser_graph *graph)
{
	char	*line;
	int		command_nb;
	int		command_nb_tmp;
	int		gnl_ret;

	command_nb = 2;
	while ((gnl_ret = get_next_line(STDIN, &line) == 1))
	{
		if (line[0] == '#')
		{
			if (line[1] == '#')
			{
				if ((command_nb_tmp = add_command(&line[2])) < 2)
					if (command_nb < 2 || !(graph->parsing_list_end = add_pars_elem(graph->parsing_list_end, line)))
					{
						free(line);
						set_msg(FAILURE, graph, MALLOC_ERROR);
						return (NULL);
					}
					command_nb = command_nb_tmp;
			}
			else if (!(graph->parsing_list_end = add_pars_elem(graph->parsing_list_end, line)))
			{
				free(line);
				set_msg(FAILURE, graph, MALLOC_ERROR);
				return (NULL);
			}
		}
		else if (add_vertex(line, graph, &command_nb) == 0)
			return(line);
		else if (!(graph->parsing_list_end = add_pars_elem(graph->parsing_list_end, line)))
		{
			free(line);
			set_msg(FAILURE, graph, MALLOC_ERROR);
			return (NULL);
		}
		free(line);
		line = NULL;
	}
	if (gnl_ret == -1)
	{
		set_msg(FAILURE, graph, "Error : read");
		return (NULL);
	}
	// else if (gnl_ret == 0)
//		add_elem(&graph->end, "");
	return (line);
}
