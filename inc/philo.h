/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goblin <goblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 04:08:26 by dgeara            #+#    #+#             */
/*   Updated: 2026/10/25 03:37:56 by goblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

# include <limits.h> // c ok ?

# define BOLD "\033[1m"
# define PURPLE "\033[35m"
# define YELLOW "\033[33m"
# define END "\033[0m"

// structs

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef struct s_philo
{
	int			id;
	int			meals_eaten;
	long		last_meal;
	pthread_t	thread;
	t_mtx		meals_mtx;
	t_mtx		*first_fork;
	t_mtx		*second_fork;
	t_table		*table;
}	t_philo;

struct s_table
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
};

// main.c
int		main(int ac, char **av);

// parse.c
int		valid_num(char *s, long *ret);
int		parse(int ac, char **av, t_table *table);

//init.c
int	set_table(t_table *table);
//utils.c
void	ft_putstr_fd(char *s, int fd);

#endif