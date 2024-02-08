/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 10:13:43 by gbrunet           #+#    #+#             */
/*   Updated: 2023/11/12 18:19:12 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	print_c(t_opt opts, va_list *ap)
{
	char	c;

	c = (char)va_arg(*ap, int);
	if (!opts.minus)
		print_c_i(' ', opts.width - 1);
	ft_putchar_fd(c, 1);
	if (opts.minus)
		print_c_i(' ', opts.width - 1);
	return (max(1, opts.width));
}
