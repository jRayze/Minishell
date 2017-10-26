/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 09:05:18 by jamerlin          #+#    #+#             */
/*   Updated: 2017/10/22 18:10:43 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_pustr_len(char *str, int n)
{
	int		i;

	i = -1;
	if (n < 0)
	{
		while (str[i++] && i < ft_strlen(str) + n)
			ft_putchar(str[i]);
	}
	else
	{
		while (str[i++] && i < n)
			ft_putchar(str[i]);
	}
}

void		print_final_echo(char **args, int pos, int ends, int starts)
{
	if (ends && starts)
		ft_pustr_len(args[pos] + 1, -1);
	else if (ends)
		ft_pustr_len(args[pos], -1);
	else if (starts)
		ft_putstr(args[pos] + 1);
	else
		ft_putstr(args[pos]);
}

static void	print_echo(char **args, int pos, char **envi)
{
	int	starts;
	int	ends;
	int	len;

	starts = (args[pos][0] == '"' || args[pos][0] == '\'') ? 1 : 0;
	len = ft_strlen(args[pos]);
	ends = (args[pos][len - 1] == '"' || args[pos][0] == '\'') ? 1 : 0;
	if (args[1][0] == '~')
	{
		if (args[1][1] && args[1][1] != '/')
		{
			ft_putstr("minishell: no such file or directory: ");
			ft_putstr(args[1] + 1);
		}
		else
		{
			ft_putstr(ft_get_elem(envi, "HOME"));
			if (args[1][1] == '/')
				ft_putstr(args[1] + 1);
		}
	}
	else
		print_final_echo(args, pos, ends, starts);
	if (args[pos + 1])
		ft_putchar(' ');
}

int			echo_built(char **args, char **envi)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (!args[1])
	{
		ft_putchar('\n');
		return (1);
	}
	else if (args[1][0] == '-' && args[1][1] == 'n' && args[1][2] == '\0')
		flag = 1;
	if (flag)
		i++;
	while (args[i])
	{
		print_echo(args, i, envi);
		i++;
	}
	if (flag == 0)
		ft_putchar('\n');
	else
		ft_putstr("%\n");
	return (1);
}
