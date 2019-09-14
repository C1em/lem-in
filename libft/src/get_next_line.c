/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coremart <coremart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 17:20:49 by coremart          #+#    #+#             */
/*   Updated: 2019/09/10 07:58:42 by coremart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>

static t_fd		*ft_fdnew(char *content, int fd)
{
	t_fd	*new;

	if (!(new = (t_fd*)malloc(sizeof(t_fd))))
		return (NULL);
	if (!(new->content = ft_strdup(content)))
		return (NULL);
	new->fd = fd;
	new->next = NULL;
	return (new);
}

static t_fd		*ft_get_fd(t_fd **lst, const int fd)
{
	t_fd		*tmp;

	tmp = *lst;
	if (!*lst)
		return ((*lst = ft_fdnew("\0", fd)));
	while (1)
	{
		if (tmp->fd == fd)
			return (tmp);
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	return ((tmp->next = ft_fdnew("\0", fd)));
}

static char		*ft_cpyfromcr(char *str)
{
	char	*tmp;
	char	*strchr;

	tmp = str;
	if (!(strchr = ft_strchr(tmp, '\n')))
	{
		free(str);
		return (NULL);
	}
	if (!(str = ft_strdup(strchr + 1)))
		return (NULL);
	free(tmp);
	return (str);
}

char			*ft_join_n_free(char *s1, const char *s2)
{
	char	*tmp;

	tmp = s1;
	if (!(s1 = ft_strjoin(tmp, s2)))
		return (NULL);
	free(tmp);
	return (s1);
}

int				get_next_line(const int fd, char **line)
{
	static t_fd		*lst;
	t_fd			*cur;
	char			buff[BUFF_SIZE + 1];
	ssize_t			rd;

	if (fd < 0 || !line || BUFF_SIZE < 0 || read(fd, buff, 0) < 0)
		return (-1);
	cur = ft_get_fd(&lst, fd);
	if (!(cur->content))
		return (0);
	while (!ft_strchr(cur->content, '\n') && (rd = read(fd, buff, BUFF_SIZE)))
	{
		buff[rd] = '\0';
		if (!(cur->content = ft_join_n_free(cur->content, buff)))
			return (-1);
	}
	if (!cur->content[0])
		return (0);
	if (!(*line = ft_strndup(cur->content, ft_strclen(cur->content, '\n'))))
		return (-1);
	if (!(cur->content = ft_cpyfromcr(cur->content)))
		return (-1);
	return (1);
}
