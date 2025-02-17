/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 21:19:53 by lilmende          #+#    #+#             */
/*   Updated: 2025/02/17 09:13:04 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ph_init_forks_and_mutexes(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (ph_p_err("Error: malloc failed\n"));
	if (pthread_mutex_init(&data->print_mutex, NULL) \
		|| pthread_mutex_init(&data->sim_mutex, NULL))
		return (ph_p_err("Error: mutex init failed\n"));
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (ph_p_err("Error: mutex init failed\n"));
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->philo_mutex[i], NULL))
			return (ph_p_err("Error: mutex init failed\n"));
		i++;
	}
	return (0);
}

int	ph_create_philosopher_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->threads[i], NULL, ph_routine, \
			&data->philosophers[i]))
			return (ph_p_err("Error: create thread failed\n"));
		i++;
	}
	return (0);
}

int	ph_init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	data->philosophers = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philosophers)
		return (ph_p_err("Error: malloc failed\n"));
	while (i < data->num_philos)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].last_meal_time = ph_g_rel_time(data);
		data->philosophers[i].times_eaten = 0;
		data->philosophers[i].left_fork = &data->forks[i];
		data->philosophers[i].right_fork = \
			&data->forks[(i + 1) % data->num_philos];
		data->philosophers[i].data = data;
		i++;
	}
	return (0);
}

int	ph_join_philosopher_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_join(data->threads[i], NULL))
			return (ph_p_err("Error: thread join failed\n"));
		i++;
	}
	return (0);
}
