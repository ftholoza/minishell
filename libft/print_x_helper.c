/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 18:48:20 by gbrunet           #+#    #+#             */
/*   Updated: 2023/11/29 16:19:33 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	x_len(unsigned int nb)
{
	size_t	len;

	len = 0;
	while (nb / 16)
	{
		nb /= 16;
		len++;
	}
	return (len + 1);
}

size_t	calc_x_size(unsigned int x, t_opt opts)
{
	size_t	len;

	if (x == 0 && opts.dot == 0 && opts.width != 1)
		return (0);
	len = 0;
	len += x_len(x);
	if (opts.zero)
		len += opts.width;
	return (len);
}

size_t	calc_x_nb_size(unsigned int x, t_opt opts)
{
	size_t	len;

	len = 0;
	if (x == 0 && opts.dot == 0)
		return (len);
	else
	{
		len++;
		while (x / 16)
		{
			x /= 16;
			len ++;
		}
		return (max(opts.dot, len));
	}
}

size_t	calc_x_space(unsigned int x, t_opt opts)
{
	size_t	nb_size;

	nb_size = calc_x_nb_size(x, opts);
	if (opts.dot != -1 || !opts.zero)
		return (max(0, opts.width - nb_size));
	return (0);
}

size_t	calc_x_zero(unsigned int x, t_opt opts)
{
	size_t	nb_size;

	nb_size = calc_x_nb_size(x, opts);
	if (opts.dot != -1)
		return (max(0, opts.dot - nb_size));
	else
		return (max(0, opts.width - nb_size));
}
