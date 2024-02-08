/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 10:02:18 by gbrunet           #+#    #+#             */
/*   Updated: 2023/11/29 16:14:24 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_int_sign(t_opt opts, int d)
{
	if (d < 0)
		ft_putchar_fd('-', 1);
	if (opts.plus && d >= 0)
		ft_putchar_fd('+', 1);
	if (opts.space && !opts.plus && d >= 0)
		ft_putchar_fd(' ', 1);
}

size_t	get_int_size(t_opt opts, int d)
{
	size_t	len;
	size_t	sign;

	if (d == 0 && opts.dot == 0)
		return (0 + opts.width);
	sign = 0;
	if (opts.space || opts.plus || d < 0)
		sign = 1;
	len = max(ft_intlen(d) + sign, opts.dot + sign);
	len = max(len, opts.width);
	return (len);
}

size_t	calc_size(int d, t_opt opts)
{
	size_t	len;

	if (d == 0 && opts.dot == 0)
		return (0);
	len = 0;
	if (opts.plus || opts.space || d < 0)
		len = 1;
	len += ft_intlen(d);
	if (opts.zero)
		len += opts.width;
	return (len);
}

size_t	calc_size_zero(int d, t_opt opts)
{
	size_t	len;

	if (d == 0 && opts.dot == 0)
		return (opts.width - max(calc_size(d, opts), opts.dot));
	len = 0;
	if (opts.plus || opts.space || d < 0)
		len = 1;
	len += ft_intlen(d);
	return (len);
}

size_t	print_d(t_opt opts, va_list *ap)
{
	int	d;

	d = va_arg(*ap, int);
	if (!opts.minus)
		print_c_i(' ', calc_space(d, opts));
	print_int_sign(opts, d);
	if (opts.zero)
		print_c_i('0', calc_zero(d, opts));
	if (opts.dot != -1)
		print_c_i('0', opts.dot - ft_intlen(d));
	if (!(opts.dot == 0 && d == 0))
		print_d_num(d);
	if (opts.minus)
		print_c_i(' ', opts.width - max(calc_size(d, opts), calc_dot(d, opts)));
	return (get_int_size(opts, d));
}
