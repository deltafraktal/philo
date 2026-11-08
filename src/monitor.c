/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goblin <goblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 02:54:26 by goblin            #+#    #+#             */
/*   Updated: 2026/11/07 22:10:37 by goblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// void end_simulation
#include "../inc/philo.h"

int	dead_philo(t_philo *philo)
{
	long	last_meal;

	pthread_mutex_lock(&philo->meals_mtx);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->meals_mtx);
	return (get_time() - last_meal > philo->table->time_to_die);
}

int	all_finished_eating(t_table *table, t_philo *philo)
{
	int	i;
	int	n;

	i = 0;
	if (table->must_eat == -1)
		return (0);
	while (i < table->nb_philo)
	{
		pthread_mutex_lock(&philo[i].meals_mtx);
		n = philo[i].meals_eaten;
		pthread_mutex_unlock(&philo[i].meals_mtx);
		if (n < table->must_eat)
			return (0);
		i++;
	}
	pthread_mutex_lock(&table->data_mtx);
	table->stop = 1;
	pthread_mutex_unlock(&table->data_mtx);
	return (1);
}

void	monitor(t_table *table)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < table->nb_philo)
		{
			if (dead_philo(&table->philos[i]))
			{
				pthread_mutex_lock(&table->print_mtx);
				pthread_mutex_lock(&table->data_mtx);
				table->stop = 1;
				pthread_mutex_unlock(&table->data_mtx);
				printf("%ld %d died\n", get_time() - table->start_time,
					table->philos[i].id);
				pthread_mutex_unlock(&table->print_mtx);
				return ;
			}
			i++;
		}
		if (all_finished_eating(table, table->philos))
			return ;
	}
}
