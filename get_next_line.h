/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 10:15:13 by pstringe          #+#    #+#             */
/*   Updated: 2018/02/23 21:52:52 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"
# include <fcntl.h>
# define BUFF_SIZE 1
# define CHERRY 0
# define POP 1

typedef struct	s_buf
{
	int		ret;
	char	*content;
}				t_buf;

typedef struct	s_feed
{
	int		ret;
	int		cherry;
	char	*line;
	char	*cut;
	char	*mark;
}				t_feed;

/*
** get next mother_fucking line
*/

int		get_next_line(const int fd, char **line);

/*
** just for debugging
*/

void	*format_line(char *line);

#endif
