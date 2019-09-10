/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 17:29:22 by cbenoit           #+#    #+#             */
/*   Updated: 2019/09/10 17:41:34 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"

int				fill_option(char **av)
{
	int		i;
	int		j;

	i = 0;
	while (++i < 4 && av[i])
	{
		if (av[i][0] == '-')
		{
			j = 0;
			while (av[i][++j])
			{
				if (av[i][j] == 'c')
					main->flag[0] = 1;
				else if (av[i][j] == 'v')
					main->flag[1] = 1;
				else if (av[i][j] == 'n')
					main->flag[2] = 1;
				else if (av[i][j] == 'a')
					main->flag[3] = 1;
				else if (av[i][j] == 's')
					main->flag[4] = 1;
				else if (av[i][j] == 'p')
					main->flag[5] = 1;
				else
					return (set_msg(FAILURE, main, "Error: wrong argument"));
			}
		}
		else
			return (set_msg(FAILURE, main, "Error: wrong argument"));
	}
	return (SUCCESS);
}
