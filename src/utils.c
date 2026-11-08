/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goblin <goblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 00:57:54 by goblin            #+#    #+#             */
/*   Updated: 2026/11/08 19:01:23 by goblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
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
