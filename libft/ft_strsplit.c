/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 18:22:50 by jamerlin          #+#    #+#             */
/*   Updated: 2017/10/26 01:13:14 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int		ft_strlen_tab(char const *str, char c)
{
	int i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (i);
}

static int		ft_caltab(char const *str, char c)
{
	int i;
	int j;
	int tab;

	i = 0;
	j = 0;
	tab = 0;
	while (str && str[i])
	{
		if (tab == 0 && str[i] != c)
		{
			tab = 1;
			j++;
		}
		else if (tab == 1 && str[i] == c)
			tab = 0;
		i++;
	}
	return (j);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**buff;
	int		i;
	int		tab;

	if (!(s))
		return (NULL);
	i = 0;
	tab = ft_caltab(s, c);
	if (!(buff = (char **)malloc(sizeof(char *) * (tab + 1))))
		return (NULL);
	while (i < tab)
	{
		while (*s == c)
			s++;
		buff[i] = ft_strsub(s, 0, ft_strlen_tab(s, c));
		s = s + ft_strlen_tab(s, c);
		i++;
	}
	buff[i] = NULL;
	return (buff);
}
