/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 07:41:09 by coremart          #+#    #+#             */
/*   Updated: 2019/09/10 07:47:59 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void		check_graph(t_parser_graph *graph)
{
	if (graph->ants <= 0 || graph->commands.s < 0 || graph->commands.t < 0)
		error_input();
}
