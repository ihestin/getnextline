/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihestin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 13:35:04 by ihestin           #+#    #+#             */
/*   Updated: 2017/12/25 17:23:14 by ihestin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

t_bufs	*struc_elem(int fd, tbufs **stb)
{
	t_bufs	**ret;

	ret = stb;
	while (*ret && (*ret)->ffd != fd)
		ret = &(*ret->next);
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

	nb = read(buff->fdd, buff->buf, BUFF_SIZE);
	if (nb >= 0)
	{
		buff->sizeb = (size_t)nb;
		ret = (nb == 0) ? nb : 2;
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
	if (!*l)
		*l = ft_strdup(b->buf);
	else
	{
		tmp = *l;
		*l = ft_strjoin(tmp, b->buf);
		free(tmp);
	}
	ret = (i == b->sizeb) ? 2 : 1;
	if (i == b->sizeb)
		b->sizeb = 0;
	else
	{
		b->sizeb = (b->sizeb - ++i);
		b->buf = (char*)ft_memmove((void*)(b->buf),
				(void*)(b->buf + i), b->sizeb - i);
	}
	return ((!l) ? -1 : ret);
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
		ft_memdel(*line);
	ret = 2;
	while (ret == 2)
	{
		if (buff->sizeb == 0)
			ret = readnextb(buff);
		if (ret > 0)
			ret = get_next(line, buff);
	}
	if (ret < 0)
		ft_memdel(*line);
	return (ret);
}
