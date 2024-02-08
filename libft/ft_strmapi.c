/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <gbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 08:26:19 by gbrunet           #+#    #+#             */
/*   Updated: 2023/11/10 08:28:11 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	size_t	strlen;
	char	*str;

	if (!f || !s)
		return (NULL);
	strlen = ft_strlen(s);
	str = malloc((strlen + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (*s)
	{
		str[i] = (*f)(i, *s);
		i++;
		s++;
	}
	str[i] = 0;
	return (str);
}
