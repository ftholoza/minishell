/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_VERIFAVEC_printf(NULL).c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 19:46:19 by gbrunet           #+#    #+#             */
/*   Updated: 2023/11/24 15:45:49 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	print_value(t_opt options, va_list *ap)
{
	size_t	len;

	len = 1;
	if (options.type == 'c')
		len = print_c(options, ap);
	if (options.type == 's')
		len = print_s(options, ap);
	if (options.type == 'p')
		len = print_p(options, ap);
	if (options.type == 'd' || options.type == 'i')
		len = print_d(options, ap);
	if (options.type == 'u')
		len = print_u(options, ap);
	if (options.type == 'x' || options.type == 'X')
		len = print_x(options, ap);
	return (len);
}

size_t	updt_count(const char *format, t_opt *opts, va_list *ap, size_t *i)
{
	size_t	add;
	size_t	count;

	count = 0;
	add = percent_parser(format, opts);
	if ((*opts).type)
	{
		*i += add;
		count += print_value(*opts, ap) - 1;
	}
	else
		ft_putchar_fd('%', 1);
	return (count);
}

size_t	parser(const char *format, va_list *ap)
{
	size_t	i;
	t_opt	options;
	size_t	count;

	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
			count += updt_count(&format[i], &options, ap, &i);
		else
			ft_putchar_fd(format[i], 1);
		i++;
		count++;
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	size_t	count;

	if (format == NULL)
		return (-1);
	va_start(ap, format);
	count = parser(format, &ap);
	va_end(ap);
	return (count);
}
