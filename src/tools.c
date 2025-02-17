/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:42:20 by lilmende          #+#    #+#             */
/*   Updated: 2025/02/17 09:42:35 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ph_stop_sim(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->sim_mutex);
	stop = data->stop_sim;
	pthread_mutex_unlock(&data->sim_mutex);
	return (stop);
}

void	ph_print_message(t_philo *philo, const char *message)
{
	if (!ph_stop_sim(philo->data))
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d %s\n", ph_g_rel_time(philo->data), philo->id, message);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
}

void	set_forks(pthread_mutex_t **ft, pthread_mutex_t **sc, t_philo *ph)
{
	if (ph->id % 2 == 0)
	{
		usleep(50);
		*ft = ph->left_fork;
		*sc = ph->right_fork;
	}
	else
	{
		*ft = ph->right_fork;
		*sc = ph->left_fork;
	}
}

int	ph_wait_for_time(t_philo *philo, long duration)
{
	long	t_start;

	t_start = ph_g_rel_time(philo->data);
	while ((ph_g_rel_time(philo->data) - t_start) < duration)
	{
		if (ph_stop_sim(philo->data))
			return (0);
		usleep(200); ////
	}
	return (1);
}
