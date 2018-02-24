/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 10:15:13 by pstringe          #+#    #+#             */
/*   Updated: 2018/02/24 15:55:55 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"
# include <fcntl.h>
# define BUFF_SIZE 6

typedef struct	s_buf
{
	int		ret;
	char	*content;
}				t_buf;

typedef struct	s_status
{
	int		started;
	int		needs_line;
	int		can_feed;
	int		can_trim;
	int		ret;
}				t_status;

typedef struct	s_feed
{
	int				ret;
	struct s_status	status;
	char			*line;
	char			*cut;
	char			*mark;
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
