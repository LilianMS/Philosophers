/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 23:27:39 by lilmende          #+#    #+#             */
/*   Updated: 2024/12/06 19:59:59 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (ph_stop_sim(philo->data))
		return ;
	set_forks(&first_fork, &second_fork, philo);
	pthread_mutex_lock(first_fork);
	if (!ph_stop_sim(philo->data))
		ph_print_died(philo, "has taken a fork");
	else
	{
		pthread_mutex_unlock(first_fork);
		return ;
	}
	pthread_mutex_lock(second_fork);
	if (!ph_stop_sim(philo->data))
		ph_print_died(philo, "has taken a fork");
	else
	{
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
		return ;
	}
}

void	eat(t_philo *philo)
{
	int		i;

	i = philo->id - 1;
	if (ph_stop_sim(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->philo_mutex[i]);
	philo->last_meal_time = ph_g_rel_time(philo->data);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->data->philo_mutex[i]);
	ph_print_message(philo, "is eating");
	wait_for_time(philo, philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleep_and_think(t_philo *philo)
{
	if (ph_stop_sim(philo->data))
		return ;
	ph_print_message(philo, "is sleeping");
	if (!wait_for_time(philo, philo->data->time_to_sleep))
		return ;
	ph_print_message(philo, "is thinking");
}

void	*ph_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philos == 1)
	{
		ph_print_message(philo, "has taken a fork");
		usleep(philo->data->time_to_die * 1000);
		ph_print_message(philo, "died");
		pthread_mutex_lock(&philo->data->sim_mutex);
		philo->data->stop_sim = 1;
		pthread_mutex_unlock(&philo->data->sim_mutex);
		return (NULL);
	}
	while (!ph_stop_sim(philo->data))
	{
		take_forks(philo);
		if (ph_stop_sim(philo->data))
			break ;
		eat(philo);
		if (ph_stop_sim(philo->data))
			break ;
		sleep_and_think(philo);
	}
	return (NULL);
}
