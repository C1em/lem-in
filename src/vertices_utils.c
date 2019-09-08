/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertices_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 21:57:19 by coremart          #+#    #+#             */
/*   Updated: 2019/09/08 05:26:05 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "libft.h"
#include <stdlib.h>

void			add_comment(char line[])
{
	return ;
}

static int				add_command(char line[])
{
	int	i;

	i = 0;
	while (i < 2 && ft_strcmp(line, (((char*[2]){"start", "end"})[i])) != SAME)
		i++;
	return (i);
}

char				*get_name(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != ' ')
		if (line[i++] == '-')
			return (NULL);
	return (ft_strndup(line, i));
}

static int				add_vertex(char line[], t_parser_graph *graph, int *command_nb)
{
	if (graph->start->vertex.name == NULL)
		graph->start->vertex.name = get_name(line);
	else
		add_elem(&graph->end, line);
	if (*command_nb == 0)
		graph->commands.s = graph->end->vertex.nb;
	else if (*command_nb == 1)
		graph->commands.t = graph->end->vertex.nb;
	*command_nb = 2;
	if (graph->end->vertex.name == NULL)
		return (0);
	return (1);
}

int				get_vertex(char *str, t_vertex_list *start)
{
	while (start && ft_strcmp(start->vertex.name, str) != SAME)
		start = start->next;
/*	if (!start)
		error();
*/	return (start->vertex.nb);

}

t_parser_graph	*pars_vertices(void)
{
	char			*line;
	t_parser_graph	*graph;
	int				command_nb;

	if (!(graph = (t_parser_graph*)malloc(sizeof(t_parser_graph))))
		exit(1);
	graph->start = init_list();
	graph->end = graph->start;
	command_nb = 2;
	if (get_next_line(STDIN, &line) != 1)
		return (NULL);
	graph->ants = ft_atoi(line);
	while (get_next_line(STDIN, &line) == 1)
	{
		if (line[0] == '#')
		{
			if (line[1] == '#')
				command_nb = add_command(&line[2]);
			else
				add_comment(line);
		}
		else if (add_vertex(line, graph, &command_nb) == 0)
		{
			pars_edges(graph, line);
			break;
		}
		free(line);
	}
	return (graph);
}
