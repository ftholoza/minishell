/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbrunet <guill@umebrunet.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:36:58 by gbrunet           #+#    #+#             */
/*   Updated: 2024/01/22 20:53:53 by gbrunet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

void	rand_to_visible_char(char *rand, int nb_char)
{
	int	i;

	i = -1;
	while (++i < nb_char)
	{
		rand[i] = ft_abs(rand[i]) % 62;
		if (rand[i] < 10)
			rand[i] += '0';
		else if (rand[i] < 36)
			rand[i] += 'A' - 10;
		else
			rand[i] += 'a' - 36;
	}
}

char	*get_random_char(int nb_char)
{
	int		fd_rand;
	char	*rand;
	int		r;

	fd_rand = open("/dev/urandom", O_RDONLY);
	if (fd_rand < 0)
		return (err_null("minishell: unable to get random chars"));
	rand = malloc(sizeof(char) * (nb_char + 1));
	if (!rand)
		return (err_null("minishell: malloc error"));
	r = read(fd_rand, rand, nb_char);
	if (r < 0)
		return (err_null("minishell: unable to read random chars"));
	rand[nb_char] = 0;
	close(fd_rand);
	rand_to_visible_char(rand, nb_char);
	return (rand);
}
