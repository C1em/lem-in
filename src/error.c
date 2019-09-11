/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 05:13:11 by coremart          #+#    #+#             */
/*   Updated: 2019/09/11 13:14:36 by cbenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem-in.h"
// #include <unistd.h>
// #include <stdlib.h>

void	error_sys(void)
{
	exit(1);
}

void	error_input(void)
{
	write(1, "ERROR\n", 6);
	exit(1);
}
