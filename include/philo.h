/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:57:16 by lilmende          #+#    #+#             */
/*   Updated: 2025/02/17 10:19:22 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>

# define MSG_ERR "Error: philosophers <= 0 or > 200 or times <= 60 ms."
# define MSG_ARG "Use: ./philo [n_ph] [t_die] [t_eat] [t_sleep] [n_of_meals]*"
# define MSG_EXS "Example: ./philo 5 800 200 200 2"

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

struct s_philo
{
	int				id;
	long			last_meal_time;
	int				times_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
} ;

struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_meals;
	long			start_time;
	int				stop_sim;
	t_philo			*philosophers;
	pthread_t		*threads;
	pthread_t		monitor_thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	sim_mutex;
	pthread_mutex_t	*philo_mutex;
} ;

int		ph_create_philosopher_threads(t_data *data);
int		ph_join_philosopher_threads(t_data *data);
void	*ph_monitor_routine(void *arg);
void	*ph_routine(void *arg);
int		ph_init_philosophers(t_data *data);
int		ph_init_forks_and_mutexes(t_data *data);
void	ph_cleanup_data(t_data *data);
void	ph_print_message(t_philo *philo, const char *message);
int		ph_stop_sim(t_data *data);
int		ph_init_data(t_data *data);
int		ph_parse_arguments(t_data *data, int ac, char **av);
int		ft_atoi(const char *nptr);
int		ph_p_err(const char *message);
long	ph_g_rel_time(t_data *data);
long	ph_g_time(void);
void	ph_print_died(t_philo *philo, const char *message);
void	set_forks(pthread_mutex_t **ft, pthread_mutex_t **sc, t_philo *ph);
int		ph_wait_for_time(t_philo *philo, long duration);

#endif
