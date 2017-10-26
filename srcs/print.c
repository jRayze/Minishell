/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 12:50:38 by jamerlin          #+#    #+#             */
/*   Updated: 2017/10/26 14:52:03 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_error_cd(char *path)
{
	ft_putstr("cd: ");
	if (access(path, F_OK) == -1)
		ft_putstr("no such file or directory: ");
	else if (access(path, R_OK) == -1)
		ft_putstr("permission denied: ");
	else
		ft_putstr("not a directory: ");
	ft_putendl(path);
}

void		print_error(char **newargs, int turn, int env_cmd, int k)
{
	if (newargs && newargs[0] && newargs[0][0]
		&& newargs[0][0] == '\n')
	{
		ft_putstr("minishell: command not found: ");
		ft_putendl(newargs[0]);
	}
	else if (turn == 1)
	{
		if (newargs[k] != NULL && is_cmd(newargs[k]) != 3
			&& nb_char_in_str(newargs[k], '=') == 0)
		{
			ft_putstr("env:");
			ft_putstr(" No such file or directory: ");
			ft_putendl(newargs[k]);
		}
	}
	else if (env_cmd == 0)
	{
		ft_putstr("minishell: command not found: ");
		ft_putendl(newargs[0]);
	}
}

void		ft_print_env(char **envi)
{
	int	i;

	i = 0;
	while (envi && envi[i])
	{
		ft_putendl(envi[i]);
		i++;
	}
}
