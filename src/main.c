/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goblin <goblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 04:08:17 by dgeara            #+#    #+#             */
/*   Updated: 2026/10/26 00:43:52 by goblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/* void	debug_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		printf("philo %d : first = forks[%ld], second = forks[%ld]\n",
			table->philos[i].id,
			table->philos[i].first_fork - table->forks,
			table->philos[i].second_fork - table->forks);
		i++;
	}
} */

int	main(int ac, char **av)
{
	t_table	table;

	if (!parse(ac, av, &table))
	{
		ft_putstr_fd("Error: invalid arguments ➜ use ./philo "
			"number_of_philosophers time_to_die time_to_eat time_to_sleep "
			"[number_of_times_each_philosopher_must_eat]\n", 2);
		return (1);
	}
	if (!set_table(&table))
		return (1);
	debug_forks(&table);
	/* if (!launch_) */
	return (0);
}
