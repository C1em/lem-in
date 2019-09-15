/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 03:19:29 by coremart          #+#    #+#             */
/*   Updated: 2019/09/15 11:59:23 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"
#include <stdlib.h>
#include <unistd.h>

t_parsing_list	*init_pars_list(char *line)
{
	t_parsing_list *list;

	if (!(list = (t_parsing_list*)malloc(sizeof(t_parsing_list))))
		return (NULL);
	list->next = NULL;
	if (!(list->line = ft_strdup(line)))
	{
		free(list);
		return (NULL);
	}
	return (list);
}

t_parsing_list	*add_pars_elem(t_parsing_list *end, char *line)
{
	t_parsing_list *new;

	if (!(new = (t_parsing_list*)malloc(sizeof(t_parsing_list))))
		return (NULL);
	new->next = NULL;
	if (!(new->line = ft_strdup(line)))
	{
		free(new);
		return (NULL);
	}
	return ((end->next = new));
}

void			print_parsing_list(t_parsing_list *list)
{
	char	str[LEM_IN_BUFF_SIZE];
	int		index;
	int		len;

	index = 0;
	while (list)
	{
		if ((len = ft_strlen(list->line)) + 1 >= LEM_IN_BUFF_SIZE - index)
		{
			write(1, str, index);
			index = 0;
		}
		ft_strcpy(&str[index], list->line);
		index += len;
		list = list->next;
		ft_strcpy(&str[index++], "\n");
	}
	if (1 >= LEM_IN_BUFF_SIZE - index)
	{
		write(1, str, index);
		index = 0;
	}
	ft_strcpy(&str[index], "\n");
	write(1, str, index + 1);
}
