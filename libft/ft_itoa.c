/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <gbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 07:56:49 by gbrunet           #+#    #+#             */
/*   Updated: 2023/11/10 08:34:26 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_strlen(int n)
{
	size_t	strlen;

	if (n == 0)
		return (1);
	strlen = 0;
	if (n < 0)
		strlen = 1;
	while (n / 10)
	{
		strlen++;
		n /= 10;
	}
	return (strlen + 1);
}

char	*ft_itoa(int n)
{
	size_t	strlen;
	char	*strnum;
	long	nb;
	int		sign;

	nb = n;
	strlen = get_strlen(nb);
	sign = 0;
	if (nb < 0)
	{
		sign = 1;
		nb = -nb;
	}
	strnum = malloc((strlen + 1) * sizeof(char));
	if (!strnum)
		return (NULL);
	strnum[strlen] = 0;
	while (strlen-- > 0 + (size_t)sign)
	{
		strnum[strlen] = nb % 10 + '0';
		nb /= 10;
	}
	if (sign)
		strnum[0] = '-';
	return (strnum);
}
