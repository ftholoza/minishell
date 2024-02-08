/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <gbrunet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:17:22 by gbrunet           #+#    #+#             */
/*   Updated: 2023/11/29 16:17:42 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	calc_u_nb_size(unsigned int u, t_opt opts)
{
	size_t	len;

	len = 0;
	if (u == 0 && opts.dot == 0)
		return (len);
	else
	{
		len++;
		while (u / 10)
		{
			u /= 10;
			len ++;
		}
		return (max(opts.dot, len));
	}
}

size_t	calc_u_space(unsigned int u, t_opt opts)
{
	size_t	nb_size;

	nb_size = calc_u_nb_size(u, opts);
	if (opts.dot != -1 || !opts.zero)
		return (max(0, opts.width - nb_size));
	return (0);
}

size_t	calc_u_zero(unsigned int u, t_opt opts)
{
	size_t	nb_size;

	nb_size = calc_u_nb_size(u, opts);
	if (opts.dot != -1)
		return (max(0, opts.dot - nb_size));
	else
		return (max(0, opts.width - nb_size));
}
