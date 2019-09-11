/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 07:41:09 by coremart          #+#    #+#             */
/*   Updated: 2019/09/11 13:46:00 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

void		check_graph(t_parser_graph *graph)
{
	if (graph->ants <= 0)
		graph->msg = "Error : wrong ant number";
	else if (graph->commands.s < 0)
		graph->msg = "Error : room start not define";
	else if (graph->commands.t < 0)
		graph->msg = "Error : room end not define";
	else
		return ;
	error_input();
}
