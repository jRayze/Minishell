/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 11:17:14 by jamerlin          #+#    #+#             */
/*   Updated: 2017/10/26 14:31:56 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_tild(char **args, char **envi, char *path_home)
{
	int		len;
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	len = ft_strlen((const char *)args[1]);
	if (len == 1)
	{
		ft_memdel((void **)&args[1]);
		change_path_env(path_home, 0, envi, args);
		ft_memdel((void **)&path_home);
		return (1);
	}
	else
	{
		tmp = ft_strsub(args[1], 1, len);
		tmp2 = ft_strjoin(path_home, tmp);
		change_path_env(tmp2, 0, envi, args);
		ft_memdel((void **)&args[1]);
		ft_memdel((void **)&tmp);
		ft_memdel((void **)&tmp2);
	}
	return (0);
}

int			is_tiret(char **args, char **envi, char *path_home)
{
	char	*tmp;

	tmp = NULL;
	if (args[1] && ft_strequ(args[1], "--"))
	{
		change_path_env(path_home, 0, envi, args);
		ft_memdel((void **)&path_home);
		ft_memdel((void **)&args[1]);
		return (1);
	}
	else if (args[1] && args[1][0] && (args[1][0] == '-') && !args[1][1])
	{
		tmp = ft_get_elem(envi, "OLDPWD");
		change_path_env(tmp, 1, envi, args);
		ft_memdel((void **)&path_home);
		ft_memdel((void **)&tmp);
		return (1);
	}
	change_path_env(args[1], 0, envi, args);
	return (0);
}

int			ft_change_pwd_next(char **env, char *tmp2, char *typ, char **tmp)
{
	int i;

	if ((i = 0) && g_j == 0 && (ft_strcmp(tmp[g_j], "~") == 0
		|| ft_strcmp(tmp[g_j], "--") == 0))
	{
		tmp2 = ft_get_elem(env, "HOME");
		i = set_env_var(typ, tmp2, env);
	}
	else if (g_j == 0 && ft_strcmp(tmp[g_j], "-") == 0)
	{
		tmp2 = ft_get_elem(env, "OLDPWD");
		i = set_env_var(typ, tmp2, env);
	}
	else if (g_j == 0 && ft_strcmp(tmp[g_j], ".") == 0)
		i = (i == 0) ? 1 : i;
	else if (ft_strcmp(tmp[g_j], "..") == 0)
	{
		if (ft_strcmp(env[g_point_point], "PWD=") != 0)
		{
			tmp2 = ft_cut_path(ft_get_elem(env, typ), '/');
			i = set_env_var(typ, tmp2, env);
			ft_memdel((void**)&tmp2);
		}
	}
	return (i);
}

void		ft_change_pwd(char *typ, char **env, char *args)
{
	char	**tmp;
	char	*tmp2;
	char	*tmp3;
	int		i;

	g_j = 0;
	g_point_point = pos_type(typ, env);
	tmp = ft_strsplit(args, '/');
	while (tmp[g_j] != NULL)
	{
		if (ft_change_pwd_next(env, tmp2, typ, tmp) == 0)
		{
			tmp2 = ft_get_elem(env, typ);
			tmp3 = ft_strjoin(tmp2, "/");
			ft_memdel((void **)&tmp2);
			tmp2 = ft_strjoin(tmp3, tmp[g_j]);
			set_env_var(typ, tmp2, env);
			ft_memdel((void **)&tmp3);
		}
		ft_memdel((void **)&tmp2);
		g_j++;
	}
	ft_free_str_double_tab(tmp);
}

int			attrib_value(int *is_i, int i)
{
	*is_i = 1;
	i--;
	return (i);
}
