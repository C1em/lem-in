/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 05:13:11 by coremart          #+#    #+#             */
/*   Updated: 2019/09/10 07:49:00 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

void	error_sys(void)
{
	exit(1);
}

void	error_input(void)
{
	write(1, "ERROR\n", 6);
	exit(1);
}
