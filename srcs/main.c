/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 13:22:42 by jamerlin          #+#    #+#             */
/*   Updated: 2017/10/26 03:30:31 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

char		*ft_get_dir(char **envi, char *s1)
{
	char	*var1;
	char	*tmp;

	var1 = ft_get_elem(envi, s1);
	if (!var1)
		return (NULL);
	tmp = ft_cut_beg_path(var1, '/');
	free(var1);
	if (!tmp)
		return (NULL);
	return (tmp);
}

int			minishell(int ac, char **av, char *line, char **envi)
{
	char	**newenv;
	char	**newargs;
	char	*tmp;

	newenv = ft_init_env(ac, av, envi);
	while (42)
	{
		print_prompt(envi);
		signal(SIGINT, SIG_IGN);
		if (signal(SIGINT, handle_signal2) == SIG_ERR)
			return (0);
		if (get_next_line(0, &line) != 1)
			return (-1);
		if ((newargs = ft_parse_input(line, newargs)) != NULL)
			if ((newenv = exec_cmd(0, &newargs, newenv, envi)) == NULL)
				return (-1);
		if (newargs)
			ft_free_str_double_tab(newargs);
		ft_memdel((void **)&line);
	}
	ft_memdel((void **)newenv);
	ft_memdel((void **)envi);
	return (0);
}

int			main(int argc, char **argv, char **envi)
{
	char	*line;
	int		ret;
	int		i;
	char	**envi2;

	i = 0;
	envi2 = NULL;
	if (argc > 1)
	{
		ft_putstr_fd("minishell : usage : ", 2);
		ft_putendl_fd(argv[0], 2);
		return (0);
	}
	ret = 0;
	line = NULL;
	if (!envi || !envi[0])
		envi2 = create_env();
	else
		envi2 = ft_init_env(argc, argv, envi);
	minishell(argc, argv, line, envi2);
	return (0);
}
