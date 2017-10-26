/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <jamerlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 13:23:10 by jamerlin          #+#    #+#             */
/*   Updated: 2017/10/24 12:56:59 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		pos_type(char *type, char **envi)
{
	int	i;

	i = 0;
	while (str_is(envi[i], type) == 0)
		i++;
	return (i);
}

char	*ft_cut_path(char *str, char c)
{
	int		i;
	char	*tmp;

	i = ft_strlen(str);
	while (str[i] != c && i)
		i--;
	if (!(tmp = (char *)malloc(sizeof(char) * i)))
		return (NULL);
	tmp = ft_strncpy(tmp, str, i);
	ft_memdel((void**)&str);
	str = ft_strdup(tmp);
	ft_memdel((void**)&tmp);
	return (str);
}

char	*ft_cut_beg_path(char *str, char c)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	i = ft_strlen(str);
	j = i;
	k = 0;
	while (str[i] != c && i)
		i--;
	if (!(tmp = (char *)malloc(sizeof(char) * j - i + 1)))
		return (NULL);
	while (str[i])
	{
		tmp[k] = str[i];
		i++;
		k++;
	}
	tmp[k] = 0;
	ft_memdel((void**)&str);
	return (tmp);
}

void	print_pwd(char **envi)
{
	char	*tmp;

	tmp = ft_get_elem(envi, "PWD");
	if (tmp)
		ft_putendl(tmp);
	ft_memdel((void **)&tmp);
}

int		nb_case(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
