/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_managment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 12:34:32 by jamerlin          #+#    #+#             */
/*   Updated: 2017/10/26 01:40:04 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_realloc(char **envi, int cpt, char *name)
{
	int		cpt2;
	char	**tab;

	cpt2 = 0;
	if (!(tab = (char **)malloc(sizeof(char *) * (cpt + 2))))
		return (NULL);
	while (envi && envi[cpt2] && cpt2 < cpt)
	{
		tab[cpt2] = ft_strdup(envi[cpt2]);
		cpt2++;
	}
	tab[cpt2] = ft_strdup(name);
	cpt2++;
	tab[cpt2] = NULL;
	ft_free_str_double_tab(envi);
	return (tab);
}

char	**ft_desalloc(char **envi, int cpt, char *name)
{
	int		cpt2;
	int		case_tab;
	char	**tab;

	cpt2 = 0;
	case_tab = 0;
	if (!(tab = (char **)malloc(sizeof(char *) * (cpt))))
		return (NULL);
	while (envi[cpt2] && cpt2 <= cpt)
	{
		if (str_is(envi[cpt2], name) != 1)
		{
			tab[case_tab] = ft_strdup(envi[cpt2]);
			case_tab++;
		}
		cpt2++;
	}
	tab[case_tab] = NULL;
	return (tab);
}

char	**ft_desalloc_first(char **args, int cpt)
{
	int		cpt2;
	int		case_tab;
	char	**tab;

	cpt2 = 0;
	case_tab = 0;
	if (!(tab = (char **)malloc(sizeof(char *) * (cpt))))
		return (NULL);
	while (args[cpt2] && cpt2 <= cpt)
	{
		if (cpt2 != 0)
		{
			tab[case_tab] = ft_strdup(args[cpt2]);
			case_tab++;
		}
		cpt2++;
	}
	tab[case_tab] = NULL;
	return (tab);
}

char	**ft_desalloc_case(char **args, int cpt, int cases)
{
	int		cpt2;
	int		case_tab;
	char	**tab;

	cpt2 = 0;
	case_tab = 0;
	if (!args || !(tab = (char **)malloc(sizeof(char *) * (cpt + 1))))
		return (NULL);
	while (args[cpt2])
	{
		if (cpt2 != cases)
		{
			tab[case_tab] = ft_strdup(args[cpt2]);
			case_tab++;
		}
		free(args[cpt2]);
		cpt2++;
	}
	tab[case_tab] = NULL;
	free(args);
	return (tab);
}
