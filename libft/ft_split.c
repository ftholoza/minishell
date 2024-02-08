/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <gbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:00:36 by gbrunet           #+#    #+#             */
/*   Updated: 2023/11/10 08:26:42 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	parts_counter(char const *s, char c)
{
	int	parts;

	parts = 0;
	while (*s)
	{
		while (*s != c && *s)
			s++;
		parts++;
		while (*s == c && *s)
			s++;
	}
	return (parts);
}

static int	get_parts(char **tab, char const *s, char c)
{
	int		index;
	size_t	len;
	int		i;

	index = 0;
	i = 0;
	while (s[index])
	{
		len = 0;
		while (s[index + len] != c && s[index + len])
			len++;
		tab[i] = ft_substr(s, index, len);
		if (!tab[i])
		{
			while (--i >= 0)
				free(tab[i]);
			return (0);
		}
		while (s[index + len] == c && s[index + len])
			len++;
		i++;
		index += len;
	}
	return (1);
}

static void	*free_clean(char *cleanstr, char **tab)
{
	free(cleanstr);
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	*cleanstr;
	int		parts;
	char	**tab;
	char	cleaner[2];

	cleaner[0] = c;
	cleaner[1] = 0;
	cleanstr = ft_strtrim(s, cleaner);
	if (!cleanstr)
		return (NULL);
	parts = parts_counter(cleanstr, c);
	tab = malloc(parts * sizeof(char *) + sizeof(NULL));
	if (!tab)
	{
		free(cleanstr);
		return (NULL);
	}
	if (!get_parts(tab, cleanstr, c))
		free_clean(cleanstr, tab);
	tab[parts] = NULL;
	free(cleanstr);
	return (tab);
}
