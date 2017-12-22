/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihestin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 13:41:35 by ihestin           #+#    #+#             */
/*   Updated: 2017/12/22 14:56:53 by ihestin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 1024

typedef struct	s_buffd
{
	int			ffd;
	char		buf[BUFF_SIZE];
	t_buffd		*next;
}				t_buffd;

#endif
