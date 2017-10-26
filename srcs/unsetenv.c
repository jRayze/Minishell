/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 12:34:47 by jamerlin          #+#    #+#             */
/*   Updated: 2017/10/24 13:03:10 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_unsetenv(char *name, char **envi, char **newargs)
{
	int	cpt;
	int	j;

	cpt = 0;
	j = 0;
	if (newargs[2])
		ft_putendl("unsetenv : Too many arguments.");
	else
	{
		while (envi[cpt])
		{
			if (j == 0)
				j = str_is(envi[cpt], name);
			cpt++;
		}
		if (j == 1)
			envi = ft_desalloc_case(envi, cpt, pos_type(name, envi));
	}
	return (envi);
}
