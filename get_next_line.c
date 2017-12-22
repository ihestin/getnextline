/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihestin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 13:35:04 by ihestin           #+#    #+#             */
/*   Updated: 2017/12/22 14:56:45 by ihestin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>



int		get_next_line(const int fd, char **line)
{
	static t_buff	*buff;
	char			*buffer;
	int				i;
	
	buffer = initbuff(fd, buff);

printf("fd = %d et indice %d et buff %s\n",fd, i, buffer);
if (line)
	;
return(0);

}
