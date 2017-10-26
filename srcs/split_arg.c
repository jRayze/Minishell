/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 18:05:17 by jamerlin          #+#    #+#             */
/*   Updated: 2017/10/26 11:23:19 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strlen_tab_arg(char const *str, char c, char d, char e)
{
	int	i;

	i = 0;
	if (str[i] && str[i] != d)
	{
		while (str[i] && str[i] != c && str[i] != e)
			i++;
	}
	else if (str[i] && str[i] == d)
	{
		i++;
		while (str[i] && str[i] != d)
			i++;
		if (str[i] && str[i] == d)
			i++;
	}
	return (i);
}

static int	ft_caltab_arg(char const *str, char c, char d, char e)
{
	int			j;
	const char	*first = str;

	j = 0;
	while (*str)
	{
		if ((*(str) >= 35 && *(str) <= 126)
				&& (first == str || str[-1] == c || str[-1] == e))
			j++;
		if (*str == d)
		{
			str++;
			j++;
			while (*(str) && *(str) != d)
				str++;
			if (*(str) == 0 && str[-1] != d)
				return (0);
		}
		str++;
	}
	return (j);
}

char		**parse_split(char const *s, int tab, char **buff)
{
	if (!(s))
		return (NULL);
	if (tab == 0 || (nb_char_in_str((char *)s, '\"') % 2 == 1))
	{
		ft_putendl("error: close quote");
		return (NULL);
	}
	if (!(buff = (char **)malloc(sizeof(char *) * (tab + 1))))
		return (NULL);
	return (buff);
}

char		**ft_strsplit_args(char const *s, char c, char d, char e)
{
	char	**buff;
	int		i;
	int		tab;

	i = -1;
	tab = ft_caltab_arg(s, c, d, e);
	if (!(buff = parse_split(s, tab, buff)))
		return (NULL);
	while (++i < tab)
	{
		while (*s == c || *s == e)
			s++;
		if (*s != d)
		{
			buff[i] = ft_strsub(s, 0, ft_strlen_tab_arg(s, c, d, e));
			s = s + ft_strlen_tab_arg(s, c, d, e);
		}
		else
		{
			buff[i] = ft_strsub(s, 1, ft_strlen_tab_arg(s, c, d, e) - 2);
			s = s + ft_strlen_tab_arg(s, c, d, e);
		}
	}
	buff[i] = NULL;
	return (buff);
}

char		**do_the_split(char **envi, char *tmp, char **path, int *i)
{
	if (envi && (tmp = ft_get_elem(envi, "PATH")) != NULL)
	{
		path = ft_strsplit(tmp, ':');
		free(tmp);
	}
	*i = -1;
	return (path);
}
