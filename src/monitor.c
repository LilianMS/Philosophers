/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 21:18:29 by lilmende          #+#    #+#             */
/*   Updated: 2024/12/06 20:37:48 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ph_print_died(t_philo *philo, const char *message)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d %s\n", ph_g_rel_time(philo->data), philo->id, message);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	check_philosophers(t_data *data, int *all_fed)
{
	t_philo		*philo;
	long		current_time;
	int			i;

	current_time = ph_g_rel_time(data);
	i = 0;
	while (i < data->num_philos)
	{
		philo = &data->philosophers[i];
		pthread_mutex_lock(&data->philo_mutex[i]);
		if ((current_time - philo->last_meal_time) > data->time_to_die)
		{
			pthread_mutex_lock(&data->sim_mutex);
			data->stop_sim = 1;
			pthread_mutex_unlock(&data->sim_mutex);
			ph_print_died(philo, "died");
			pthread_mutex_unlock(&data->philo_mutex[i]);
			return (1);
		}
		if (data->nbr_of_meals > 0 && philo->times_eaten < data->nbr_of_meals)
			*all_fed = 0;
		pthread_mutex_unlock(&data->philo_mutex[i]);
		i++;
	}
	return (0);
}

void	*ph_monitor_routine(void *arg)
{
	t_data	*data;
	int		all_fed;

	data = (t_data *)arg;
	while (1)
	{
		if (ph_stop_sim(data))
			break ;
		all_fed = 1;
		if (check_philosophers(data, &all_fed))
			break ;
		if (all_fed && data->nbr_of_meals > 0)
		{
			pthread_mutex_lock(&data->sim_mutex);
			data->stop_sim = 1;
			pthread_mutex_unlock(&data->sim_mutex);
			break ;
		}
		usleep(100);
	}
	return (NULL);
}
