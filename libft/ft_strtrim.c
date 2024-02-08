/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <gbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:19:26 by gbrunet           #+#    #+#             */
/*   Updated: 2023/12/07 11:14:49 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char const c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static char	*empty_str(void)
{
	char	*emptystr;

	emptystr = malloc(sizeof (char));
	if (!emptystr)
		return (NULL);
	*emptystr = 0;
	return (emptystr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*trimmed;
	int				strlen;
	unsigned int	start;

	if (!s1)
		return (NULL);
	if (*set == 0)
		return (ft_strdup(s1));
	strlen = ft_strlen(s1) - 1;
	while (strlen >= 0 && is_in_set(s1[strlen], set))
		strlen--;
	if (strlen == -1)
		trimmed = empty_str();
	else
	{
		start = 0;
		while (is_in_set(s1[start++], set))
			strlen--;
		trimmed = ft_substr(s1, --start, ++strlen);
	}
	return (trimmed);
}
