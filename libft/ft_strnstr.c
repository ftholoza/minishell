/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <gbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:47:34 by gbrunet           #+#    #+#             */
/*   Updated: 2023/11/10 08:25:11 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (*little == 0)
		return ((char *)big);
	i = 0;
	j = 0;
	while (i < len && big[i])
	{
		while (i + j < len && big[i + j] && big[i + j] == little[j])
			j++;
		if (little[j] == 0)
			return ((char *)(big + i));
		j = 0;
		i++;
	}
	return (NULL);
}
