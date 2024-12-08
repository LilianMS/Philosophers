/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 23:15:41 by lilmende          #+#    #+#             */
/*   Updated: 2024/12/06 20:17:06 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	destroy_mutexes(pthread_mutex_t *mutexes, int count)
{
	int	i;

	if (mutexes)
	{
		i = 0;
		while (i < count)
		{
			pthread_mutex_destroy(&mutexes[i]);
			i++;
		}
		free(mutexes);
	}
}

static void	free_resources(void *resource)
{
	if (resource)
		free(resource);
}

void	ph_cleanup_data(t_data *data)
{
	destroy_mutexes(data->philo_mutex, data->num_philos);
	destroy_mutexes(data->forks, data->num_philos);
	free_resources(data->philosophers);
	free_resources(data->threads);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->sim_mutex);
}
