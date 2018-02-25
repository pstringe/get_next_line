/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 10:13:13 by pstringe          #+#    #+#             */
/*   Updated: 2018/02/24 17:28:01 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** gets buffer from file descriptor
*/

t_buf	*get_buf(const int fd)
{
	t_buf	*buf;

	buf = ft_memalloc(sizeof(t_buf));
	buf->content = ft_strnew(BUFF_SIZE + 1);
	buf->ret = read(fd, buf->content, BUFF_SIZE);
	return (buf);
}

/*
** gets feed of buffers from file descriptor 
*/

void	feed(const int fd, t_feed *trimed)
{
	t_buf	*buf;
	char	*n;

	n = NULL;
	buf = get_buf(fd);
	trimed->line = (!trimed->status.started) ? ft_strnew(0) : trimed->line;
	trimed->status.started = 1;
	while (buf->ret > 0 && !n)
	{
		trimed->line = ft_strjoin(trimed->line, buf->content);
		if ((n = ft_strchr(buf->content, '\n')))
			break ;
		ft_memdel((void**)&(buf->content));
		ft_memdel((void**)&buf);
		buf = get_buf(fd);
	}
	trimed->status.can_feed = (buf->ret > 0);
	trimed->status.needs_line = 0;
	trimed->status.ret = buf->ret;
	trimed->cut = n;
	trimed->mark = strchr(trimed->cut, '\n');
	ft_memdel((void**)&buf);
}

/*
** trims line off of feed
*/

void	trim(t_feed *untrimed, char **line)
{
	int len;
	
	*(untrimed->cut) = '\0';
	*line = ft_strnew((len = ft_strlen(untrimed->line)));
	ft_memccpy(*line, untrimed->line, '\n', len + 1);
	untrimed->line = (strchr(untrimed->line, '\n') + 1);
	untrimed->cut = strchr(untrimed->line, '\n');
	untrimed->mark = strchr(untrimed->mark, '\n');
	untrimed->status.needs_line = (!untrimed->cut) ? 1 : 0;
}

/*
** gets next line from feed
*/

int		get_next_line(const int fd, char **line)
{
	static t_feed		untrimed;

	if ((untrimed.status.needs_line && untrimed.status.can_feed) || !untrimed.status.started)
		feed(fd, &untrimed);
	if (!untrimed.status.needs_line)
		trim(&untrimed, line);
	return (untrimed.status.ret);
}

/*
** test remove after
*/

int		main(int argc, char **argv)
{
	char	*line;
	int		fd;
	int		ret;

	if (argc != 2)
	{
		ft_putendl("must specify file to read from");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	while ((ret = get_next_line(fd, &line) && line) > 0)
	{
		ft_putendl(format_line(line));
	}
	if (ret == -1)
		ft_putendl("error");
	if (!ret)
		ft_putendl("EOF");
	return (0);
}
