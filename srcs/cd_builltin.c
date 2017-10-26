/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builltin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 18:31:02 by jamerlin          #+#    #+#             */
/*   Updated: 2017/10/26 14:35:02 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		change_path_env(char *path, int prt_path, char **env, char **ag)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!chdir(path))
	{
		if (prt_path)
			ft_putendl(path);
		set_env_var("OLDPWD", cwd, env);
		if (ag[1] && ag[1][0] != '~' && ag[1][0] != '-')
		{
			if (ft_strcmp(ag[1], ".") != 0)
			{
				if (ag[1][0] != '/')
					ft_change_pwd("PWD", env, ag[1]);
				else
					ft_is_slash_dir("PWD", env, ag[1]);
			}
		}
		else
			set_env_var("PWD", path, env);
	}
	else
		print_error_cd(path);
	ft_memdel((void **)&cwd);
}

int			cd_error_arguments(void)
{
	ft_putendl("cd: too many arguments");
	return (1);
}

static int	has_args(char **args, char **envi)
{
	char	*cwd;
	char	*tmp;

	if (args[2])
	{
		if (args[3])
			return (cd_error_arguments());
		cwd = getcwd(NULL, 0);
		if (!(tmp = ft_replace(cwd, args[1], args[2])))
		{
			ft_putstr("cd: string not in pwd ");
			ft_putendl(args[2]);
			ft_memdel((void **)&cwd);
			free(tmp);
			return (1);
		}
		set_env_var("OLDPWD", cwd, envi);
		set_env_var("PWD", tmp, envi);
		ft_memdel((void **)&cwd);
		ft_memdel((void **)&tmp);
		return (1);
	}
	return (0);
}

void		ft_is_slash_dir(char *type, char **envi, char *args)
{
	struct dirent	*dp;
	int				i;

	i = pos_type(type, envi);
	if (access(args, F_OK) != -1)
	{
		ft_memdel((void **)&envi[i]);
		envi[i] = ft_strjoin("PWD=", args);
	}
	else
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(args);
	}
}

int			ft_exec_cd(char **envi, char **args, int i)
{
	char	*path_home;
	int		res;

	if ((path_home = ft_get_elem(envi, "HOME")) == NULL)
		return (2);
	if (!args[1])
	{
		change_path_env(path_home, 0, envi, args);
		ft_memdel((void **)&path_home);
		return (1);
	}
	if (has_args(args, envi))
	{
		ft_memdel((void **)&path_home);
		return (1);
	}
	if (args[1] && args[1][0] == '~')
		res = is_tild(args, envi, path_home);
	else
		res = is_tiret(args, envi, path_home);
	(res == 0) ? ft_memdel((void **)&path_home) : res == 1;
	return (res);
}
