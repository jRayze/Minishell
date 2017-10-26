/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 13:29:14 by jamerlin          #+#    #+#             */
/*   Updated: 2017/10/26 11:24:10 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_env(void)
{
	char	*cwd;
	char	**envi;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	if (!(envi = (char **)malloc(sizeof(char *) * (7))))
		return (NULL);
	envi[0] = ft_strdup("HOME=/Users/jamerlin");
	envi[1] = ft_strdup("LOGNAME=jamerlin");
	envi[2] = ft_strdup("SHLVL=1");
	envi[3] = ft_strjoin("PWD=", cwd);
	tmp = ft_cut_path(cwd, '/');
	envi[4] = ft_strjoin("OLDPWD=", tmp);
	envi[5] = ft_strdup("ZSH=/Users/jamerlin/.oh-my-zsh");
	envi[6] = NULL;
	free(tmp);
	return (envi);
}

char	**ft_init_env(int ac, char **av, char **envi)
{
	int		i;
	int		j;
	char	**newenv;

	(void)ac;
	i = 0;
	j = nb_case(envi);
	if (j == 0)
		return (NULL);
	if (!(newenv = (char **)ft_memalloc(sizeof(char *) * (j + 1))))
		return (NULL);
	while (envi && envi[i])
	{
		if (!(newenv[i] = ft_strdup(envi[i])))
		{
			ft_exit(av);
			return (NULL);
		}
		i++;
	}
	newenv[i] = NULL;
	return (newenv);
}
