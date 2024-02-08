/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <gbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:54:14 by gbrunet           #+#    #+#             */
/*   Updated: 2023/11/10 09:16:58 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	strlen;
	char	cc;

	strlen = ft_strlen(s);
	if (c == 0)
		return ((char *)(s + strlen));
	cc = (char)c;
	while (strlen--)
	{
		if (*(s + strlen) == cc)
			return ((char *)(s + strlen));
	}
	return (NULL);
}
