/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goblin <goblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 01:40:56 by goblin            #+#    #+#             */
/*   Updated: 2026/10/25 22:13:21 by goblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	valid_num(char *s, long *ret)
{
	long	n;

	n = 0;
	if (*s == '+')
		s++;
	if (!*s)
		return (0);
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		n = n * 10 + (*s - '0');
		if (n > INT_MAX)
			return (0);
		s++;
	}
	*ret = n;
	return (n > 0);
}

int	parse(int ac, char **av, t_table *table)
{
	int		i;
	long	tab[5];

	if (ac != 5 && ac != 6)
		return (0);
	i = 0;
	tab[4] = -1;
	while (i < ac - 1)
	{
		if (!valid_num(av[i + 1], &tab[i]))
			return (0);
		i++;
	}
	table->nb_philo = tab[0];
	table->time_to_die = tab[1];
	table->time_to_eat = tab[2];
	table->time_to_sleep = tab[3];
	table->must_eat = tab[4];
	return (1);
}
