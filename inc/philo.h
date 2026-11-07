/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goblin <goblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 04:08:26 by dgeara            #+#    #+#             */
/*   Updated: 2026/11/06 23:02:30 by goblin           ###   ########.fr       */
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
	t_mtx		*forks; //uitlisé ?
	t_mtx		print_mtx;
	t_mtx		data_mtx;
	t_philo		*philos;
};

// main.c
int		main(int ac, char **av);

// parse.c
int		valid_num(char *s, long *ret);
int		parse(int ac, char **av, t_table *table);

// init.c
void	destroy_mtx(t_table *table, int count);
int		init_mutexes(t_table *table);
void	init_philos(t_table *table);
int		set_table(t_table *table);

// time.c
long	get_time(void);
void	ft_usleep(t_table *table, long ms);
int		simulation_over(t_table *table);
void	print_status(t_philo *philo, char *msg);

// simulation.c
void	mister_lonely(t_philo *philo);
void	eat(t_philo *philo);
void	*simulation(void *arg);

// monitor.c
void	monitor(t_table *table);

//utils.c
void	ft_putstr_fd(char *s, int fd);

#endif