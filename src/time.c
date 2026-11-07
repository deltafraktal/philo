/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goblin <goblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 00:50:12 by goblin            #+#    #+#             */
/*   Updated: 2026/10/27 02:13:33 by goblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	simulation_over(t_table *table)
{
	int	is_over;

	pthread_mutex_lock(&table->data_mtx);
	is_over = table->stop;
	pthread_mutex_unlock(&table->data_mtx);
	return (is_over);
}

void	ft_usleep(t_table *table, long ms)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < ms)
	{
		if (simulation_over(table))
			return ;
		usleep(500);
	}
}

void	print_status(t_philo *philo, char *msg)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->print_mtx);
	if (!simulation_over(table))
		printf("%ld %d %s\n", (get_time() - table->start_time), philo->id, msg);
	pthread_mutex_unlock(&philo->table->print_mtx);
}
