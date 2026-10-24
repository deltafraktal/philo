/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeara <dgeara@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 04:08:26 by dgeara            #+#    #+#             */
/*   Updated: 2026/09/30 01:34:30 by dgeara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# define BOLD "\033[1m"
# define PURPLE "\033[35m"
# define YELLOW "\033[33m"
# define END "\033[0m"

// structs

typedef pthread_mutex_t	t_mtx;

typedef struct s_table
{
	int			nb_philo;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int			must_eat;
	long		start_time;
	int			stop;
	t_mtx		*forks;
	t_mtx		print_mtx;
	t_mtx		data_mtx;
	t_philo		*philos;
}	t_table;

typedef struct s_philo
{
	int			id;
	int			meal_eaten;
	long		last_meal;
	pthread_t	thread;
	t_mtx		*left_fork;
	t_mtx		*right_fork;
	t_table		*table;
}	t_philo;

// main
int		main(int ac, char **av);

//

#endif