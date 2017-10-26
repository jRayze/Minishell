/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 18:26:11 by jamerlin          #+#    #+#             */
/*   Updated: 2017/10/26 11:25:50 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		print_no_file_env(char ***newargs, char **tmp)
{
	ft_putstr("env: ");
	ft_putstr((*newargs)[1]);
	ft_putendl(" No such file or directory");
	return (-1);
}

int		if_option_i(char ***newargs, char **tmp, int i)
{
	if (i == 1)
	{
		ft_free_str_double_tab(tmp);
		return (-1);
	}
	else
		*newargs = ft_desalloc_case(*newargs, i, 1);
	if (nb_case(*newargs) == 1)
	{
		ft_free_str_double_tab(tmp);
		return (-1);
	}
	return (0);
}

void	get_args_env(char ***newargs, int is_i, char ***tmp)
{
	char	*tmp2;
	char	*tmp3;
	int		i;

	i = 0;
	while ((*newargs)[1] && (*newargs)[1][0] != '\0'
		&& nb_char_in_str((*newargs)[1], '=') == 1)
	{
		tmp2 = str_equal((*newargs)[1], 0);
		tmp3 = str_equal((*newargs)[1], 1);
		*tmp = ft_set_env(*tmp, tmp2, tmp3, "1");
		ft_memdel((void**)&tmp2);
		ft_memdel((void**)&tmp3);
		*newargs = ft_desalloc_case(*newargs, nb_case(*newargs), 1);
	}
	if (!(*newargs)[1])
	{
		ft_print_env(*tmp);
		ft_free_str_double_tab(*tmp);
		tmp = NULL;
	}
}

int		exec_env_two(char ***newargs, char **tmp, int is_i)
{
	if (nb_char_in_str((*newargs)[1], '=') == 1)
		get_args_env(newargs, is_i, &tmp);
	if (((*newargs)[1] && is_cmd((*newargs)[1]) != -1))
	{
		*newargs = ft_desalloc_case(*newargs, nb_case(*newargs), 0);
		exec_cmd_bis(0, newargs, &tmp, NULL);
		ft_free_str_double_tab(tmp);
		tmp = NULL;
		return (9);
	}
	else if ((*newargs)[1])
		return (print_no_file_env(newargs, tmp));
	return (9);
}

int		ft_exec_env(char **envi, char ***newargs)
{
	int		i;
	char	**tmp;
	int		is_i;

	is_i = 0;
	tmp = ft_dup_tab_double(envi);
	if ((i = nb_case(*newargs)) == 1)
	{
		ft_print_env(tmp);
		ft_free_str_double_tab(tmp);
	}
	if (i >= 2)
	{
		if (ft_strcmp((*newargs)[1], "-i") == 0)
		{
			i = attrib_value(&is_i, i);
			if (if_option_i(newargs, tmp, i) == -1)
				return (-1);
			ft_free_str_double_tab(tmp);
			tmp = NULL;
		}
		return (exec_env_two(newargs, tmp, is_i));
	}
	return (9);
}
