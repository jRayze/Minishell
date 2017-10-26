/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 12:47:01 by jamerlin          #+#    #+#             */
/*   Updated: 2017/10/25 19:43:03 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**ft_parse_input(char *str, char **newargs)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[j] && (str[j] == '\n' || str[j] == '\t' || str[j] == ' '))
		j++;
	if (str[j] == 0)
		return (NULL);
	tmp = ft_strtrim(str);
	newargs = ft_strsplit_args(tmp, ' ', '\"', '\t');
	ft_memdel((void **)&tmp);
	return (newargs);
}

int			is_cmd(char *path)
{
	if (!(path))
		return (-1);
	if (ft_strcmp(path, "echo") == 0)
		return (1);
	else if (ft_strcmp(path, "cd") == 0)
		return (2);
	else if (ft_strcmp(path, "env") == 0)
		return (3);
	else if (ft_strcmp(path, "setenv") == 0)
		return (4);
	else if (ft_strcmp(path, "unsetenv") == 0)
		return (5);
	else if (ft_strcmp(path, "exit") == 0)
		return (6);
	else if (path[0] == '.' && path[1] == '/')
		return (7);
	return (0);
}
