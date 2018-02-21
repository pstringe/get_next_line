/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 10:13:13 by pstringe          #+#    #+#             */
/*   Updated: 2018/02/21 10:22:06 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(const int fd, char **line)
{
	int		ret;
	char 	*buf;
	
	buf	= ft_strnew(BUFF_SIZE);
	if ((ret = read(fd, buf, BUFF_SIZE)) > 0)
		*line = buf;
	return (ret);
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
