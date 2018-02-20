/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 10:13:13 by pstringe          #+#    #+#             */
/*   Updated: 2018/02/20 11:43:35 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(const int fd, char **line)
{
	static char 	*str;
	char 			*f;
	int				bytes;
	char			buf[BUFF_SIZE + 1];
	
	bytes = -1;
	f = NULL;
	str = ft_strnew(BUFF_SIZE);
	while ((bytes = read(fd, buf, BUFF_SIZE)) > 0 && !f)
	{
		buf[BUFF_SIZE] = '\0';
		str = ft_strjoin(str, buf);
		f = strchr(str, '\n');
	}
	if (bytes < 1)
		return (bytes);
	*f = '\0';
	*line = ft_strnew(ft_strlen(str));
	f = (char*)ft_memccpy(*line, str, '\0', ft_strlen(str));
	ft_bzero((void*)str, ft_strlen(str));
	str = f;
	return (1);
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
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		ft_putendl(line);
	}
	if (ret == -1)
		ft_putendl("error");
	if (!ret)
		ft_putendl("EOF");
	return (0);
}
