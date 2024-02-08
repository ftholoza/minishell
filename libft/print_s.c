/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 10:13:43 by gbrunet           #+#    #+#             */
/*   Updated: 2023/11/29 16:13:32 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	substring(char **s, t_opt opts)
{
	char	*tempstr;

	tempstr = *s;
	*s = ft_substr(*s, 0, opts.dot);
	free(tempstr);
	if (!s)
		return (0);
	return (1);
}

size_t	print_s(t_opt opts, va_list *ap)
{
	char	*s;
	char	*initstr;
	size_t	slen;

	initstr = va_arg(*ap, char *);
	if (!initstr)
		s = ft_strdup("(null)");
	else
		s = ft_strdup(initstr);
	if (opts.dot != -1)
		if (!substring(&s, opts))
			return (0);
	if ((opts.dot != -1 && opts.dot < 6) && !initstr)
	{
		free(s);
		s = ft_strdup("");
	}
	if (!opts.minus)
		print_c_i(' ', opts.width - ft_strlen(s));
	ft_putstr_fd(s, 1);
	if (opts.minus)
		print_c_i(' ', opts.width - ft_strlen(s));
	slen = ft_strlen(s);
	free(s);
	return (max(slen, opts.width));
}
