/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 10:15:13 by pstringe          #+#    #+#             */
/*   Updated: 2018/02/21 09:56:06 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"
# include <fcntl.h>
# define BUFF_SIZE 4

typedef struct	s_line
{
	char	*begin;
	char	*con;
	char	*start;
	char	*end;
	char	*line;
}				t_line;
#endif
