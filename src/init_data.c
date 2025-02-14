/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 22:50:30 by lilmende          #+#    #+#             */
/*   Updated: 2025/02/14 18:02:22 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ph_arg_isndig(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
			{
				ph_p_err("Invalid argument: ");
				printf("%s\n%s\n", av[i], MSG_ERR);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ph_validate_arguments(t_data *data)
{
	if (data->num_philos > 200 \
		|| data->num_philos < 1 \
		|| data->time_to_die < 60 \
		|| data->time_to_eat < 60 \
		|| data->time_to_sleep < 60 \
		|| data->nbr_of_meals == 0)
	{
		ph_p_err(MSG_ERR);
		printf("\n%s\n%s\n", MSG_ARG, MSG_EXS);
		return (1);
	}
	return (0);
}

int	ph_parse_arguments(t_data *data, int ac, char **av)
{
	if ((ac < 5 || ac > 6) || ph_arg_isndig(av))
	{
		ph_p_err(MSG_ARG);
		printf("\n%s\n", MSG_EXS);
		return (1);
	}
	data->num_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nbr_of_meals = ft_atoi(av[5]);
	else
		data->nbr_of_meals = -1;
	return (ph_validate_arguments(data));
}

int	ph_init_data(t_data *data)
{
	data->start_time = ph_g_time();
	data->stop_sim = 0;
	data->philo_mutex = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->philo_mutex)
		return (ph_p_err("Error: malloc failed for mutex array\n"));
	data->threads = malloc(sizeof(pthread_t) * data->num_philos);
	if (!data->threads)
		return (ph_p_err("Error: malloc failed\n"));
	if (ph_init_forks_and_mutexes(data))
		return (1);
	if (ph_init_philosophers(data))
		return (1);
	return (0);
}
