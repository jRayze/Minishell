/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 12:47:12 by jamerlin          #+#    #+#             */
/*   Updated: 2017/10/26 03:36:36 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		str_is(char *str, char *elem)
{
	char	**tmp;
	int		i;

	i = 0;
	if (!str || !elem)
		return (0);
	tmp = ft_strsplit(str, '=');
	while (tmp && tmp[i])
	{
		if (ft_strcmp(tmp[i], elem) == 0)
		{
			ft_free_str_double_tab(tmp);
			return (1);
		}
		i++;
	}
	ft_free_str_double_tab(tmp);
	return (0);
}

void	ft_free_str_double_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		ft_memdel((void **)&tab[i]);
		i++;
	}
	ft_memdel((void **)&tab);
}

char	*create_path(char **envi, char *args, char *elem)
{
	char	*str;
	char	*backslash;
	char	*get_elem;
	char	*join;

	backslash = ft_strdup("/");
	get_elem = ft_get_elem(envi, elem);
	join = ft_strjoin(get_elem, backslash);
	str = ft_strjoin(join, args);
	free(backslash);
	free(join);
	return (str);
}

char	**ft_dup_tab_double(char **envi)
{
	int		i;
	char	**tab;

	i = 0;
	if (!(tab = (char **)malloc(sizeof(char *) * (nb_case(envi) + 1))))
		return (NULL);
	while (envi[i])
	{
		tab[i] = ft_strdup(envi[i]);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	*str_equal(char *str, int i)
{
	int		begin;
	int		final;
	char	*tmp;

	begin = 0;
	final = ft_strlen(str);
	while (str[begin] && str[begin] != '=')
		begin++;
	if (i == 0)
		tmp = ft_strsub(str, 0, begin);
	else
	{
		begin++;
		if (str[begin] == '\"')
			begin++;
		if (str[final - 1] == '\"')
			final--;
		tmp = ft_strsub(str, begin, final - begin);
	}
	return (tmp);
}
