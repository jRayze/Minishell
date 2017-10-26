/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 12:46:53 by jamerlin          #+#    #+#             */
/*   Updated: 2017/10/26 14:57:19 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_executable(char *bin_path, struct stat f, char **ag, char **env)
{
	if (f.st_mode & S_IFREG)
	{
		if (f.st_mode & S_IXUSR)
			return (run_cmd(bin_path, ag, env));
		else
		{
			ft_putstr("minishell: permission denied: ");
			ft_putendl(bin_path);
		}
		free(bin_path);
		return (1);
	}
	free(bin_path);
	return (0);
}

static int	check_if_is_binary(char **args, char **envi)
{
	int				i;
	char			*bin_path;
	char			**path;
	struct stat		f;
	char			*tmp;

	path = NULL;
	tmp = NULL;
	bin_path = NULL;
	if (lstat(args[0], &f) != -1)
		return (is_executable((bin_path = ft_strdup(args[0])), f, args, envi));
	path = do_the_split(envi, tmp, path, &i);
	while (path && path[++i] && (bin_path = dofile_path(args[0], path[i])))
	{
		if (lstat(bin_path, &f) != -1)
		{
			ft_free_str_double_tab(path);
			if (args[1] && args[1][0] == '~')
				args[1] = ft_strdup(ft_get_elem(envi, "HOME"));
			return (is_executable(bin_path, f, args, envi));
		}
		ft_memdel((void **)&bin_path);
	}
	ft_free_str_double_tab(path);
	return (0);
}

int			exec_cmd_bis(int cpt, char ***newargs, char ***newenv, char **envi)
{
	int	i;
	int	nb_arg;
	int	turn;
	int	env_cmd;

	turn = 1;
	env_cmd = 1;
	i = is_cmd((*newargs)[cpt]);
	if (i > 0)
	{
		if (i == 2)
			return (0);
		if (i == 3 && !(*newargs)[1])
			ft_print_env(*newenv);
		launch_build(i, *newenv, *newargs, envi);
	}
	if (i == 0)
	{
		if (check_if_is_binary(*newargs, *newenv) == 1)
			return (0);
		else
			print_error(*newargs, turn, env_cmd, 0);
	}
	return (-1);
}

char		**launch_build(int i, char **newenv, char **newargs, char **envi)
{
	char *tmp;

	if (i == 1)
		echo_built(newargs, newenv);
	else if (i >= 2 && i <= 5)
		newenv = is_env_var_set(newargs, newenv, envi, i);
	else if (i == 6)
	{
		if (newargs[1] && newargs[2])
		{
			ft_putendl("exit: too many arguments");
			return (newenv);
		}
		ft_exit(newargs);
		return (NULL);
	}
	else if (i == 7)
	{
		tmp = ft_strdup(newargs[0]);
		if (get_access(tmp) == 0)
			run_cmd(tmp, newargs, newenv);
	}
	return (newenv);
}

char		**exec_cmd(int cpt, char ***newargs, char **newenv, char **envi)
{
	int	i;
	int	nb_arg;
	int turn;
	int is_env;

	turn = 0;
	is_env = 0;
	i = is_cmd((*newargs)[cpt]);
	if (i == 3)
	{
		nb_arg = nb_case(*newargs);
		ft_exec_env(newenv, newargs);
		is_env = 1;
	}
	if (i > 0)
		newenv = launch_build(i, newenv, *newargs, envi);
	else if (i == 0)
	{
		if (check_if_is_binary(*newargs, newenv) == 1)
			return (newenv);
		else
			print_error(*newargs, turn, is_env, 0);
	}
	return (newenv);
}
