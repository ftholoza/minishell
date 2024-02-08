/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <gbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:14:47 by gbrunet           #+#    #+#             */
/*   Updated: 2023/11/29 16:20:31 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	calc_dot(int d, t_opt opts)
{
	size_t	len;

	len = 0;
	if (d < 0)
		len = 1;
	return (opts.dot + len);
}

size_t	calc_nb_size(int d, t_opt opts)
{
	size_t	len;

	len = 0;
	if (d == 0 && opts.dot == 0)
		return (len);
	else
	{
		len++;
		while (d / 10)
		{
			d /= 10;
			len ++;
		}
		return (max(opts.dot, len));
	}
}

size_t	calc_space(int d, t_opt opts)
{
	size_t	nb_size;

	nb_size = calc_nb_size(d, opts);
	if (d < 0)
		nb_size++;
	if (opts.dot != -1 || !opts.zero)
		return (max(0, opts.width - nb_size));
	return (0);
}

size_t	calc_zero(int d, t_opt opts)
{
	size_t	nb_size;

	nb_size = calc_nb_size(d, opts);
	if (d < 0)
		nb_size++;
	if (opts.dot != -1)
		return (max(0, opts.dot - nb_size));
	else
		return (max(0, opts.width - nb_size));
}
