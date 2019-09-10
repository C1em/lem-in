/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 07:41:09 by coremart          #+#    #+#             */
/*   Updated: 2019/09/10 16:16:53 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

void		check_graph(t_parser_graph *graph)
{
	if (graph->ants <= 0 || graph->commands.s < 0 || graph->commands.t < 0)
		error_input();
}
