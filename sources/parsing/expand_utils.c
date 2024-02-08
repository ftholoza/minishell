/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 02:29:10 by gbrunet           #+#    #+#             */
/*   Updated: 2024/02/04 19:55:24 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_var_char(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

int	is_custom_expand(char c)
{
	if (c == '0' || c == '$' || c == '?' || !is_var_char(c))
		return (1);
	return (0);
}

char	*ft_str_append(char *str, char *add)
{
	char	*new;

	new = ft_strjoin(str, add);
	free(str);
	return (new);
}
