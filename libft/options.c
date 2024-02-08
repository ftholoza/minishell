/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 09:38:48 by gbrunet           #+#    #+#             */
/*   Updated: 2023/11/12 09:47:48 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init_options(t_opt *options)
{
	options->minus = 0;
	options->zero = 0;
	options->dot = -1;
	options->hash = 0;
	options->space = 0;
	options->plus = 0;
	options->width = 0;
	options->type = 0;
}

void	set_type(t_opt *options, char c)
{
	options->type = c;
	if (c == '%')
		ft_putchar_fd('%', 1);
}

void	set_flags(t_opt *options, char c)
{
	if (c == '-')
		options->minus = 1;
	if (c == '0')
		options->zero = 1;
	if (c == '#')
		options->hash = 1;
	if (c == ' ')
		options->space = 1;
	if (c == '+')
		options->plus = 1;
}

size_t	set_precision(const char *s, t_opt *options)
{
	size_t	i;

	i = 0;
	options->dot = 0;
	while (s[++i] && ft_isdigit(s[i]))
		options->dot = options->dot * 10 + (s[i] - '0');
	return (i - 1);
}

size_t	set_width(const char *s, t_opt *options)
{
	size_t	i;

	i = 0;
	while (s[i] && ft_isdigit(s[i]))
	{
		options->width = options->width * 10 + (s[i] - '0');
		i++;
	}
	return (i - 1);
}
