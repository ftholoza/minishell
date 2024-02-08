/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <gbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:33:36 by gbrunet           #+#    #+#             */
/*   Updated: 2023/11/10 09:16:34 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	if (dest < src)
	{
		d = (unsigned char *)dest;
		s = (const unsigned char *)src;
		while (n--)
			*d++ = *s++;
	}
	else
	{
		d = (unsigned char *)dest + (n - 1);
		s = (const unsigned char *)src + (n - 1);
		while (n--)
			*d-- = *s--;
	}
	return (dest);
}
