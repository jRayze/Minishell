/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 03:47:11 by jamerlin          #+#    #+#             */
/*   Updated: 2017/10/26 04:25:21 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		actualise_env(char **newenv, char **envi)
{
	char *tmp;
	char *tmp2;

	if ((tmp = ft_get_elem(newenv, "HOME")) != NULL)
	{
		tmp2 = ft_get_elem(envi, "HOME");
		set_env_var("HOME", tmp, newenv);
		ft_memdel((void**)&tmp);
		ft_memdel((void**)&tmp2);
	}
	if ((tmp = ft_get_elem(newenv, "PWD")) != NULL)
	{
		tmp2 = ft_get_elem(envi, "PWD");
		set_env_var("PWD", tmp2, newenv);
		ft_memdel((void**)&tmp);
		ft_memdel((void**)&tmp2);
	}
	if ((tmp = ft_get_elem(newenv, "OLDPWD")) != NULL)
	{
		tmp2 = ft_get_elem(envi, "OLDPWD");
		set_env_var("OLDPWD", tmp2, newenv);
		ft_memdel((void**)&tmp);
		ft_memdel((void**)&tmp2);
	}
	return ;
}

void		is_cd_cmd(char **newargs, char **newenv, char **envi)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_get_elem(newenv, "HOME");
	tmp2 = ft_get_elem(newenv, "PWD");
	tmp3 = ft_get_elem(newenv, "OLDPWD");
	if (tmp != NULL && tmp2 != NULL && tmp3 != NULL)
	{
		ft_exec_cd(newenv, newargs, 2);
		actualise_env(envi, newenv);
	}
	else
	{
		if (ft_exec_cd(envi, newargs, 2) == 2)
			ft_putstr_fd("minishell : environnement not set\n", 2);
		actualise_env(newenv, envi);
	}
	ft_memdel((void **)&tmp);
	ft_memdel((void **)&tmp2);
	ft_memdel((void **)&tmp3);
}

char		**is_env_var_set(char **newargs, char **newenv, char **envi, int i)
{
	if (i == 2)
		is_cd_cmd(newargs, newenv, envi);
	else if (i == 4)
	{
		if (ft_check_set_env(newargs) == 0)
			newenv = ft_set_env(newenv, newargs[1], newargs[2], newargs[3]);
	}
	else if (i == 5)
		newenv = ft_unsetenv(newargs[1], newenv, newargs);
	return (newenv);
}

int			get_access(char *tmp)
{
	if (access(tmp, F_OK) == 0 && access(tmp, X_OK) == 0)
		return (0);
	else
	{
		if (access(tmp, F_OK) == -1)
			ft_putstr("minishell: no such binary process: ");
		else if (access(tmp, X_OK) == -1)
			ft_putstr("minishell: permission denied: ");
	}
	ft_putendl(tmp);
	return (-1);
}
