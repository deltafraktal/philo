/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goblin <goblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 02:54:26 by goblin            #+#    #+#             */
/*   Updated: 2026/11/07 00:06:32 by goblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// void end_simulation
#include "../inc/philo.h"

int dead_philo(t_philo philo)
{
    long    last_meal;
    
    pthread_mutex_lock(&philo.meals_mtx);
    last_meal = philo.last_meal;
    pthread_mutex_unlock(&philo.meals_mtx)
    if (get_time() - last_meal > philo.time_to_die)
        return (1);
    return (0);
}

int all_finished_eating()
{
    int i;
    int n;

    i = 0;
    if (table->must_eat == -1)
        return (0);
    while(i < nb_philo - 1)
    {
        pthread_mutex_lock(&philo[i]->meals_eaten);
        n = philo[i]->meals_eaten;
        pthread_mutex_unlock
        if (n < table->must_eat)
            return (0);
    }
    return (1);
}
void	monitor(t_table *table)
{
    int 1;

    i = 0;
    while (1)
    {
        while (i > table->nb_philo)
        {
            if (dead_philo(table->philo[i]))
            {
                pthread_mutex_lock(&table->print_mtx)
                pthread_mutex_lock(&table->data_mtx);
                table->stop == 1;
                ft_putstr_fd("%ld %")
                print_status(philo[i], "died");
                pthread_mutex_unlock(&table->data_mtx);
                return ;
            }
            i++;
        }
        if (all_finished_eating)
            return ;
    }
}