/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 17:29:22 by cbenoit           #+#    #+#             */
/*   Updated: 2019/09/10 18:45:34 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"
# include <stdarg.h> //transfer on lem-in.h ?

int				set_msg(int return_value, t_parser_graph *graph, char *msg)
{
	graph->msg = msg;
	return (return_value);
}

int		ft_break(int return_value, int n, ...)
{
	va_list		msg;

	va_start(msg, n);
	while (n--)
		ft_putstr(va_arg(msg, char*));
	ft_putchar('\n');
	va_end(msg);
	return (return_value);
}

static int		*setup_zero(int *to_init, size_t size, int value)
{
	size_t i;

	i = 0;
	while (i < size)
		to_init[i++] = value;
	return (to_init);
}

int				fill_option(t_parser_graph *graph, char **av)
{
	int		i;
	int		j;

	setup_zero(graph->flag, 6, 0); //verif size
	i = 0;
	while (++i < 4 && av[i])
	{
		if (av[i][0] == '-')
		{
			j = 0;
			while (av[i][++j])
			{
				if (av[i][j] == 'c')
					graph->flag[0] = 1;
				else if (av[i][j] == 'd')
					graph->flag[1] = 1;
				else if (av[i][j] == 'm')
					graph->flag[2] = 1;
				else if (av[i][j] == 'n')
					graph->flag[3] = 1;
				else if (av[i][j] == 'p')
					graph->flag[4] = 1;
				else if (av[i][j] == 'v')
					graph->flag[5] = 1;
				else
					return (FAILURE);
			}
		}
		else
			return (FAILURE);
	}
	return (SUCCESS);
}
