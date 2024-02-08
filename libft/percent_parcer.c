/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent_parcer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 09:50:05 by gbrunet           #+#    #+#             */
/*   Updated: 2023/11/12 18:18:43 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_flag(char c)
{
	if (c == '-' || c == '0' || c == '.' || c == '#' || c == ' ' || c == '+')
		return (1);
	return (0);
}

int	is_type(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u'
		|| c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

int	valid_flag(char c)
{
	if (is_flag(c) || is_type(c) || ft_isdigit(c))
		return (1);
	return (0);
}

size_t	percent_parser(const char *s, t_opt *options)
{
	size_t	i;

	init_options(options);
	i = 0;
	while (s[++i] && valid_flag(s[i]) && !options->type)
	{
		if (is_type(s[i]))
			set_type(options, s[i]);
		else if (s[i] == '.')
			i += set_precision(&s[i], options);
		else if (is_flag(s[i]))
			set_flags(options, s[i]);
		else if (ft_isdigit(s[i]))
			i += set_width(&s[i], options);
	}
	return (i - 1);
}
