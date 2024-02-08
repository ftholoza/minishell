/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <gbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:08:40 by gbrunet           #+#    #+#             */
/*   Updated: 2024/01/16 10:09:25 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	parts_counter(char const *s)
{
	int	parts;

	parts = 0;
	while (*s)
	{
		while (*s && !ft_isspace(*s))
			s++;
		parts++;
		while (*s && ft_isspace(*s))
			s++;
	}
	return (parts);
}

static int	get_parts(char **tab, char const *s)
{
	int		index;
	size_t	len;
	int		i;

	index = 0;
	i = 0;
	while (s[index])
	{
		len = 0;
		while (s[index + len] && !ft_isspace(s[index + len]))
			len++;
		tab[i] = ft_substr(s, index, len);
		if (!tab[i])
		{
			while (--i >= 0)
				free(tab[i]);
			return (0);
		}
		while (s[index + len] && ft_isspace(s[index + len]))
			len++;
		i++;
		index += len;
	}
	return (1);
}

char	**ft_space_split(char const *s)
{
	char	*cleanstr;
	int		parts;
	char	**tab;

	cleanstr = ft_strtrim(s, " \f\n\r\t\v");
	if (!cleanstr)
		return (NULL);
	parts = parts_counter(cleanstr);
	tab = malloc(parts * sizeof(char *) + sizeof(NULL));
	if (!tab)
	{
		free(cleanstr);
		return (NULL);
	}
	if (!get_parts(tab, cleanstr))
	{
		free(cleanstr);
		free(tab);
		return (NULL);
	}
	tab[parts] = NULL;
	free(cleanstr);
	return (tab);
}
