/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 12:34:41 by jamerlin          #+#    #+#             */
/*   Updated: 2017/10/26 14:21:10 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		set_env_var(char *type, char *val, char **envi)
{
	int		i;
	char	*tmp;

	i = pos_type(type, envi);
	tmp = ft_strjoin("=", val);
	if (envi[i] != NULL)
	{
		ft_memdel((void **)&envi[i]);
		if (val)
			envi[i] = ft_strjoin(type, tmp);
		else
			envi[i] = ft_strjoin(type, "=");
	}
	else
	{
		if (val)
			envi[i] = ft_strjoin(type, tmp);
		else
			envi[i] = ft_strjoin(type, "=");
	}
	ft_memdel((void **)&tmp);
	return (1);
}

char	**ft_set_env(char **envi, char *name, char *value, char *overwrite)
{
	int	j;

	j = 0;
	if ((j = elem_is_in_env(envi, name)) == 1)
	{
		if (!overwrite || overwrite == 0)
			return (envi);
		else
		{
			if (!(ft_atoi(overwrite)))
			{
				ft_putendl("Bad overwrite\n");
				return (NULL);
			}
			set_env_var(name, value, envi);
			return (envi);
		}
	}
	if (!(envi = ft_realloc(envi, nb_case(envi), name)))
	{
		ft_putstr("error\n");
		return (envi);
	}
	set_env_var(name, value, envi);
	return (envi);
}

int		ft_check_set_env(char **newargs)
{
	if (!(newargs[1]))
	{
		ft_putendl("usage: setenv [var_name] [value] [overwrite]");
		return (1);
	}
	if (newargs[1])
	{
		if (nb_char_in_str(newargs[1], '=') > 0)
		{
			ft_putendl("setenv : Do not put '=' on variable name.");
			return (1);
		}
		if (newargs[3])
		{
			if (newargs[4])
			{
				ft_putendl("setenv : Too many arguments.");
				return (1);
			}
			return (0);
		}
		return (0);
	}
	return (0);
}

int		elem_is_in_env(char **envi, char *name)
{
	int cpt;
	int j;

	cpt = 0;
	j = 0;
	if (!envi || !name)
		return (0);
	while (envi && envi[cpt])
	{
		if (j == 0)
			j = str_is(envi[cpt], name);
		cpt++;
	}
	return (j);
}
