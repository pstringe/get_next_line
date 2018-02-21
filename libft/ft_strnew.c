/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 14:15:54 by pstringe          #+#    #+#             */
/*   Updated: 2018/02/20 11:58:51 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *str;

	str = ft_memalloc(size + 1);
	if (!str)
	{
		return (NULL);
	}
	else
	{
		ft_memset(str, '\0', size + 1);
	}
	return (str);
}
