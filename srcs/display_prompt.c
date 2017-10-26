/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 12:46:46 by jamerlin          #+#    #+#             */
/*   Updated: 2017/10/26 14:37:08 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		handle_signal2(int sinl)
{
	ft_putstr("\n");
	ft_putstr("\033[33m");
	if (nb_char_in_str(g_dir, '/') == 1 && ft_strlen(g_dir) > 1)
		ft_putstr(g_dir + 1);
	else
		ft_putstr(g_dir);
	if (g_dir && g_dir[1] && g_dir[1] != ' ')
		ft_putchar(' ');
	ft_putstr("\033[36m");
	ft_putstr("$> ");
	ft_putstr("\033[0m");
}

void		handle_signal(int signl)
{
	if (signl == SIGINT)
	{
		ft_putstr("\n");
		signal(SIGINT, handle_signal);
	}
}

int			ft_is_home(char **envi, char *str1, char *str2)
{
	char	*var1;
	char	*var2;
	int		i;

	i = -1;
	var1 = ft_get_elem(envi, str1);
	var2 = ft_get_elem(envi, str2);
	if (!var1 || !var2)
		return (-1);
	i = ft_strcmp(var1, var2);
	free(var1);
	free(var2);
	if (i == 0)
		return (1);
	return (0);
}

void		print_color(char *str)
{
	ft_putstr("\033[36m");
	ft_putstr(str);
	ft_putstr("\033[0m");
}

void		print_prompt(char **newenv)
{
	char	*tmp;
	char	*tmp2;

	ft_putstr("\033[33m");
	tmp2 = getcwd(NULL, 0);
	if (!tmp2)
		ft_putstr(g_dir);
	else
	{
		(g_dir != NULL) ? free(g_dir) : g_dir;
		if (ft_is_home(newenv, "PWD", "HOME") == 1)
		{
			ft_putstr((g_dir = ft_strdup("~")));
			free(tmp2);
		}
		else if (tmp)
		{
			tmp = ft_cut_beg_path(tmp2, '/');
			g_dir = (nb_char_in_str(tmp, '/') == 1 && ft_strlen(tmp) > 1) ?
				ft_strdup(tmp + 1) : ft_strdup(tmp);
			ft_putstr(g_dir);
			free(tmp);
		}
	}
	print_color(" $> ");
}
