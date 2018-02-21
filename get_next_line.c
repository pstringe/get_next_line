/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 10:13:13 by pstringe          #+#    #+#             */
/*   Updated: 2018/02/21 10:41:39 by pstringe         ###   ########.fr       */
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

int		get_next_line(const int fd, char **line)
{
	t_buf	*buf;
		
	if ((buf = get_buf(fd))->ret > 0)
		*line = buf->content;
	return (buf->ret);
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
		ft_putendl(line);
	}
	if (ret == -1)
		ft_putendl("error");
	if (!ret)
		ft_putendl("EOF");
	return (0);
}
