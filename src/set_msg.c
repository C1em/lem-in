/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 15:26:05 by cbenoit           #+#    #+#             */
/*   Updated: 2019/09/15 11:59:54 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"
#include <stdarg.h>

int				set_msg(int return_value, t_parser_graph *graph, char *msg)
{
	graph->msg = msg;
	return (return_value);
}

char			*set_null_msg(t_parser_graph *graph, char *msg)
{
	graph->msg = msg;
	return (NULL);
}

int				ft_break(int return_value, int n, ...)
{
	va_list		msg;

	va_start(msg, n);
	while (n--)
		ft_putstr(va_arg(msg, char*));
	ft_putchar('\n');
	va_end(msg);
	return (return_value);
}
