/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamerlin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 14:10:43 by jamerlin          #+#    #+#             */
/*   Updated: 2016/11/18 12:20:41 by jamerlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbchar(int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	i++;
	return (i);
}

char		*ft_itoa(int n)
{
	char		*buff;
	int			len;
	long int	num;

	num = n;
	len = nbchar(n);
	if (!(buff = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (num == 0)
		buff[0] = '0';
	if (num == -2147483648)
		return (ft_strdup("-2147483648"));
	if (num < 0)
	{
		buff[0] = '-';
		num = -num;
	}
	num *= 10;
	buff[len] = '\0';
	while ((num /= 10) > 0)
		buff[--len] = (num % 10) + '0';
	return (buff);
}
