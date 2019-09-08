/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 18:19:50 by coremart          #+#    #+#             */
/*   Updated: 2019/09/08 05:25:14 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "libft.h"


t_graph			*parser(void)
{
	t_parser_graph	*graph;
	char			*line;

	graph = pars_vertices();
	return (make_graph(graph));
}
