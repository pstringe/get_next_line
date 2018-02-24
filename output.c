/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 20:16:08 by pstringe          #+#    #+#             */
/*   Updated: 2018/02/23 20:18:23 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** just a function to to sub '\n' with a marker making it easier to debug
*/
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
