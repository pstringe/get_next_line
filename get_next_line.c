/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 10:13:13 by pstringe          #+#    #+#             */
/*   Updated: 2018/02/21 17:30:25 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_buf	*get_buf(const int fd)
{
	t_buf	*buf;

	buf = ft_memalloc(sizeof(t_buf));
	buf->content = ft_strnew(BUFF_SIZE);
	buf->ret = read(fd, buf->content, BUFF_SIZE);
	return (buf);
}

t_cut	*get_uncut(const int fd, char *mark)
{
	t_buf	*buf;
	t_cut	*uncut;
	char	*n;

	uncut = ft_memalloc(sizeof(t_cut));
	uncut->cut = (!mark) ? ft_strnew(0) : mark;
	while ((buf = get_buf(fd))->ret > 0 && n)
	{
		uncut->cut = ft_strjoin(uncut->cut, buf->content);
		n = ft_strchr(buf->content, '\n');
		ft_memdel((void**)&(buf->content));
		ft_memdel((void**)&buf);
	}
	uncut->ret = buf->ret;
	uncut->mark = n;
	ft_memdel((void**)&buf);
	return (uncut);
}

/*
t_line	*get_line(char *uncut)
{
}
*/
int		get_next_line(const int fd, char **line)
{
	t_cut	*uncut;
		
	if ((uncut = get_uncut(fd, NULL))->ret > 0)
		*line = uncut->cut;
	return (uncut->ret);
}

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
		ft_putstr(line);
	}
	if (ret == -1)
		ft_putendl("error");
	if (!ret)
		ft_putendl("EOF");
	return (0);
}
