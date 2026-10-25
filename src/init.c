/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goblin <goblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 02:52:16 by goblin            #+#    #+#             */
/*   Updated: 2026/10/26 00:41:38 by goblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	destroy_mtx(t_table *table, int count)
{
	while (--count >= 0)
	{
		pthread_mutex_destroy(&table->forks[count]);
		pthread_mutex_destroy(&table->philos[count].meals_mtx);
	}
	free(table->forks);
}

int	init_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (destroy_mtx(table, i), 0);
		if (pthread_mutex_init(&table->philos[i].meals_mtx, NULL))
			return (pthread_mutex_destroy(&table->forks[i]),
				destroy_mtx(table, i), 0);
		i++;
	}
	if (pthread_mutex_init(&table->print_mtx, NULL))
		return (destroy_mtx(table, i), 0);
	if (pthread_mutex_init(&table->data_mtx, NULL))
	{
		pthread_mutex_destroy(&table->print_mtx);
		return (destroy_mtx(table, i), 0);
	}
	return (1);
}

void	init_philos(t_table *table)
{
	int	i;
	int	a;
	int	b;

	i = 0;
	while (i < table->nb_philo)
	{
		a = i;
		b = (i + 1) % table->nb_philo;
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		table->philos[i].first_fork = &table->forks[a];
		table->philos[i].second_fork = &table->forks[b];
		if (a > b)
		{
			table->philos[i].first_fork = &table->forks[b];
			table->philos[i].second_fork = &table->forks[a];
		}
		i++;
	}
}

int	set_table(t_table *table)
{
	table->stop = 0;
	table->forks = malloc(sizeof(t_mtx) * table->nb_philo);
	if (!table->forks)
		return (0);
	table->philos = malloc(sizeof(t_philo) * table->nb_philo);
	if (!table->philos)
		return (free(table->forks), 0);
	memset(table->philos, 0, sizeof(t_philo) * table->nb_philo);
	if (!init_mutexes(table))
		return (free(table->philos), 0);
	init_philos(table);
	return (1);
}
