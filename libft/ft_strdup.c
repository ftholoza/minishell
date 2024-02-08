/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <gbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:59:31 by gbrunet           #+#    #+#             */
/*   Updated: 2023/11/09 17:45:19 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	strlen;

	strlen = ft_strlen(s);
	dup = malloc((strlen + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, (strlen + 1));
	return (dup);
}
