/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 21:00:21 by lilmende          #+#    #+#             */
/*   Updated: 2024/12/06 17:28:50 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ph_parse_arguments(&data, ac, av))
		return (1);
	if (ph_init_data(&data))
	{
		ph_cleanup_data(&data);
		return (1);
	}
	pthread_create(&data.monitor_thread, NULL, ph_monitor_routine, &data);
	ph_create_philosopher_threads(&data);
	ph_join_philosopher_threads(&data);
	pthread_join(data.monitor_thread, NULL);
	ph_cleanup_data(&data);
	return (0);
}
