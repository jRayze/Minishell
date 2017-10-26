/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 11:22:19 by jamerlin          #+#    #+#             */
/*   Updated: 2017/10/26 03:38:10 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_exit(char **newargs)
{
	if (newargs[1])
	{
		if (ft_atoi(newargs[1]))
			ft_putstr_fd(newargs[1], -1);
	}
	return (0);
}

int			nb_char_in_str(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
			j++;
		i++;
	}
	return (j);
}

char		*dofile_path(char *name, char *file_path)
{
	char	*new;
	char	*buf;

	buf = ft_strjoin(file_path, "/");
	new = ft_strjoin(buf, name);
	free(buf);
	return (new);
}

char		*ft_get_elem(char **envi, char *elem)
{
	char	*path;
	int		cpt;
	int		lol;

	cpt = 0;
	if (!envi || !elem)
		return (NULL);
	while (envi && envi[cpt] != NULL)
	{
		lol = str_is(envi[cpt], elem);
		if (lol != 0)
		{
			path = ft_duplicate_path(envi[cpt], ft_strlen(envi[cpt]));
			return (path);
		}
		cpt++;
	}
	return (NULL);
}

char		*ft_duplicate_path(char *str, int size_env)
{
	char	*cpy;
	int		cpt;
	int		cpt2;

	cpt = 0;
	cpt2 = 0;
	while (str[cpt2] != '\0' && str[cpt2] != '=')
		cpt2++;
	if (str[cpt2] == '=')
		cpt2++;
	cpy = (char *)malloc(sizeof(char) * (size_env - cpt2 + 1));
	if (cpy == NULL)
		return ("error");
	while (str[cpt2] != '\0')
	{
		cpy[cpt] = str[cpt2];
		cpt2++;
		cpt++;
	}
	cpy[cpt] = '\0';
	return (cpy);
}
