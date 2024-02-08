/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <gbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 08:22:46 by gbrunet           #+#    #+#             */
/*   Updated: 2023/11/10 08:35:12 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstlen;
	size_t	srclen;

	dstlen = 0;
	srclen = 0;
	if (dst)
		dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (dstlen + 1 < size)
		ft_strlcpy(dst + dstlen, src, size - dstlen);
	if (size > dstlen)
		return (dstlen + srclen);
	return (size + srclen);
}
