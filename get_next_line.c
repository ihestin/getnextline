/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihestin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 11:09:16 by ihestin           #+#    #+#             */
/*   Updated: 2017/12/27 11:17:35 by ihestin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

t_bufs	*struc_elem(int fd, t_bufs **stb)
{
	t_bufs	**ret;

	ret = stb;
	while (*ret && (*ret)->ffd != fd)
		ret = &((*ret)->next);
	if (*ret)
		return (*ret);
	(*ret) = (t_bufs *)malloc(sizeof(t_bufs));
	if (!*ret)
		return (*ret);
	(*ret)->ffd = fd;
	(*ret)->sizeb = 0;
	return (*ret);
}

int		readnextb(t_bufs *buff)
{
	ssize_t		nb;
	int			ret;

	nb = read(buff->ffd, buff->buf, BUFF_SIZE);
	if (nb >= 0)
	{
		buff->sizeb = (size_t)nb;
		ret = (nb == 0) ? 0 : 2;
	}
	else
		ret = -1;
	return (ret);
}

int		get_next(char **l, t_bufs *b)
{
	size_t	i;
	char	*tmp;
	int		ret;

	i = 0;
	while (i < b->sizeb && (b->buf)[i] != '\n')
		i++;
	(b->buf)[i] = '\0';
	tmp = *l;
	*l = (*l) ? ft_strjoin(tmp, b->buf) : ft_strdup(b->buf);
	if (tmp)
		free(tmp);
	ret = (i == b->sizeb) ? 2 : 1;
	if (i == b->sizeb)
		b->sizeb = 0;
	else
	{
		b->sizeb = (b->sizeb - ++i);
		b->p = ft_memmove((void*)(b->buf),
				(void*)(b->buf + i), b->sizeb);
	}
	return ((!(*l)) ? -1 : ret);
}

int		get_next_line(const int fd, char **line)
{
	static t_bufs	*stb;
	t_bufs			*buff;
	int				ret;

	buff = struc_elem(fd, &stb);
	if (!line || !buff)
		return (-1);
	if (*line)
		ft_memdel((void**)line);
	ret = 2;
	while (ret == 2)
	{
		if (buff->sizeb == 0)
			ret = readnextb(buff);
		if (ret > 0)
			ret = get_next(line, buff);
	}
	if (ret < 0)
		ft_memdel((void**)line);
	return (ret);
}
