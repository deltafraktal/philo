/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goblin <goblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 04:08:17 by dgeara            #+#    #+#             */
/*   Updated: 2026/11/08 07:08:14 by goblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	cleanup(t_table *table)
{
	destroy_mtx(table, table->nb_philo);
	pthread_mutex_destroy(&table->print_mtx);
	pthread_mutex_destroy(&table->data_mtx);
	free(table->philos);
}

void	join_threads(t_philo *philos, int philos_count)
{
	int	i;

	i = 0;
	while (i < philos_count)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

int	start_simulation(t_table *table)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = table->philos;
	table->start_time = get_time();
	while (i < table->nb_philo)
	{
		philos[i].last_meal = table->start_time;
		if (pthread_create(&philos[i].thread, NULL, simulation, &philos[i]))
		{
			pthread_mutex_lock(&table->data_mtx);
			table->stop = 1;
			pthread_mutex_unlock(&table->data_mtx);
			join_threads(philos, i);
			return (0);
		}
		i++;
	}
	monitor(table);
	join_threads(philos, i);
	return (1);
}

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
		return (ft_putstr_fd("Error: init failed\n", 2), 1);
	if (!start_simulation(&table))
	{
		cleanup(&table);
		return (ft_putstr_fd("Error: thread creation failed\n", 2), 1);
	}
	cleanup(&table);
	return (0);
}
