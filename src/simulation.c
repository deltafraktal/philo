/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goblin <goblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 02:25:58 by goblin            #+#    #+#             */
/*   Updated: 2026/11/07 22:21:25 by goblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	mister_lonely(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	print_status(philo, "has taken a fork");
	ft_usleep(philo->table, philo->table->time_to_die);
	pthread_mutex_unlock(philo->first_fork);
}

void	think(t_philo *philo)
{
	long	think_time;
	t_table	*table;

	table = philo->table;
	print_status(philo, "is thinking");
	if (table->nb_philo % 2 == 0)
		think_time = table->time_to_eat - table->time_to_sleep;
	else
		think_time = 2 * table->time_to_eat - table->time_to_sleep;
	if (think_time > 0)
		ft_usleep(table, think_time);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->second_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->meals_mtx);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meals_mtx);
	print_status(philo, "is eating");
	ft_usleep(philo->table, philo->table->time_to_eat);
	pthread_mutex_lock(&philo->meals_mtx);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_mtx);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

void	*simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->nb_philo == 1)
		return (mister_lonely(philo), NULL);
	if (philo-> id % 2 == 0)
		think(philo);
	while (!simulation_over(philo->table))
	{
		eat(philo);
		print_status(philo, "is sleeping");
		ft_usleep(philo->table, philo->table->time_to_sleep);
		think(philo);
	}
	return (NULL);
}
