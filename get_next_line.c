/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 10:13:13 by pstringe          #+#    #+#             */
/*   Updated: 2018/02/22 20:15:58 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** just a function to to sub '\n' with a marker making it easier to debug
*/
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*s1;
	const char	*s2;

	s1 = (char *)dst;
	s2 = (const char *)src;
	while (n-- != 0)
	{
		*s1++ = *s2++;
	}
	return (dst);
}
void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char			*s1;
	const char		*s2;
	unsigned char	cc;

	s1 = (char *)dst;
	s2 = (const char *)src;
	cc = (unsigned char)c;
	while (n-- != 0)
	{
		if ((unsigned char)*s2 != cc)
		{
			ft_memcpy(s1, s2, 1);
			s1++;
			s2++;
		}
		else
		{
			ft_memcpy(s1, s2, 1);
			s1++;
			return (s1);
		}
	}
	return (NULL);
}
void	*format_line(char *line)
{
	int  i;
	char f;
	char *str;

	str = ft_strnew(ft_strlen(line));
	f = 'A';
	i = -1;
	while (line[++i])
	{
		if (line[i] == '\n')
		{
			str[i] = f;
			f++;
		}
		else
			str[i] = line[i];
	}
	return (str);
}

t_buf	*get_buf(const int fd)
{
	t_buf	*buf;

	buf = ft_memalloc(sizeof(t_buf));
	buf->content = ft_strnew(BUFF_SIZE + 1);
	buf->ret = read(fd, buf->content, BUFF_SIZE);
	return (buf);
}

t_cut	*get_untrimed(const int fd, t_cut **trimed)
{
	t_buf	*buf;
	t_cut	*untrimed;
	char	*n;

	n = NULL;
	untrimed = (!trimed) ? ft_memalloc(sizeof(t_cut)): trimed;
	buf = get_buf(fd);
	while (buf->ret > 0 && !n)
	{
		untrimed->cut = (!untrimed->cut) ? buf->content : ft_strjoin(untrimed->cut, buf->content);
		if((n = ft_strchr(buf->content, '\n')))
			break ;
		ft_memdel((void**)&(buf->content));
		ft_memdel((void**)&buf);
		buf = get_buf(fd);
	}
	untrimed->ret = buf->ret;
	untrimed->mark = n;
	ft_memdel((void**)&buf);
	return (untrimed);
}

char	**trim(t_cut **untrimed, char **line)
{
	char	*str;
	char	*new_cut;
	char	*n;
	int		clen;
	int		nlen;

	str = NULL;
	new_cut = NULL;
	n = NULL;
	ft_memdel((void**)line);
	*line = NULL;
	if ((n = strchr((*untrimed)->cut, '\n')))
	{
		*n = '\0';
		clen = ft_strlen((*untrimed)->cut);
		*line = ft_strnew(clen); 
		ft_memccpy(*line, (*untrimed)->cut, *n, clen);
		(*untrimed)->cut = (n + 1);
		new_cut = ft_strnew((nlen = ft_strlen((*untrimed)->cut)));
		ft_memcpy(new_cut, (*untrimed)->cut, nlen);
		ft_memdel((void**)((*untrimed)->cut));
		(*untrimed)->cut = new_cut;
	}
	return (!*line) ? NULL: line;
}

int		get_next_line(const int fd, char **line)
{
	static t_cut	*untrimed;
	int				l;

	line = (l = (untrimed && untrimed->mark)) ? trim(&untrimed, line) : line;
	untrimed = (!untrimed) ? get_untrimed(fd, NULL) : untrimed;
	if (!l)
	{
		l = !!(line = trim(&untrimed, line));
		if (untrimed->ret > 0)
			untrimed = get_untrimed(fd, &untrimed);
	}
	return (untrimed->ret);
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
		ft_putendl(format_line(line));
	}
	if (ret == -1)
		ft_putendl("error");
	if (!ret)
		ft_putendl("EOF");
	return (0);
}
