/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <gbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:05:48 by gbrunet           #+#    #+#             */
/*   Updated: 2023/11/09 17:48:09 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	char	*ptr;
	size_t	strlen;
	size_t	sublen;

	if (!s)
		return (NULL);
	strlen = ft_strlen(s);
	if (strlen < start + 1)
		sublen = 0;
	else if (strlen < len + start)
		sublen = strlen - start;
	else
		sublen = len;
	substr = malloc(sizeof(char) * (sublen + 1));
	if (!substr)
		return (NULL);
	ptr = substr;
	while (sublen--)
		*ptr++ = *(s++ + start);
	*ptr = 0;
	return (substr);
}
