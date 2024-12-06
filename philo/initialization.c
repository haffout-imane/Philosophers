/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihaffout <ihaffout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:53:00 by ihaffout          #+#    #+#             */
/*   Updated: 2024/06/25 14:24:12 by ihaffout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parse_parameters(int ac, char **av, t_parameters *params)
{
	if (ac != 5 && ac != 6)
		return (1);
	params->num_philo = ft_atoi(av[1]);
	params->time_die = ft_atoi(av[2]);
	params->time_eat = ft_atoi(av[3]) * 1000;
	params->time_sleep = ft_atoi(av[4]) * 1000;
	if (params->num_philo <= 0 || params->time_die == -1 
		|| params->time_eat == -1000 || params->time_sleep == -1000)
		return (1);
	if (ac == 6)
	{
		params->eat_limit = ft_atoi(av[5]);
		if (params->eat_limit == -1)
			return (1);
	}
	else
		params->eat_limit = -1;
	return (0);
}

int	init_mutexes(t_parameters *params)
{
	if (pthread_mutex_init(&(params->write), NULL))
		return (1);
	if (pthread_mutex_init(&(params->mutex), NULL))
	{
		pthread_mutex_destroy(&(params->write));
		return (1);
	}
	return (0);
}

int	forks_init(t_parameters *params)
{
	int	i;

	i = 0;
	params->forks = malloc(sizeof(pthread_mutex_t) * params->num_philo);
	if (!params->forks)
		return (1);
	while (i < params->num_philo)
	{
		if (pthread_mutex_init(&params->forks[i], NULL))
		{
			while (i > 0)
				pthread_mutex_destroy(&params->forks[--i]);
			free(params->forks);
			pthread_mutex_destroy(&(params->write));
			pthread_mutex_destroy(&(params->mutex));
			return (1);
		}
		i++;
	}
	return (0);
}

int	philosophers_init(t_philosopher *philosophers, t_parameters *params)
{
	int	i;

	i = 0;
	while (i < params->num_philo)
	{
		philosophers[i].id = i + 1;
		philosophers[i].right_fork = &params->forks[i];
		philosophers[i].left_fork = &params->forks[(i + 1) % params->num_philo];
		philosophers[i].meals_eaten = 0;
		philosophers[i].params = params;
		philosophers[i].full = 0;
		i++;
	}
	return (0);
}

int	init_all(t_parameters *params, t_philosopher *philosophers)
{
	if (init_mutexes(params))
	{
		print_error("Failed to initialize mutexes");
		return (1);
	}
	if (forks_init(params))
	{
		print_error("Failed to initialize forks");
		return (1);
	}
	philosophers_init(philosophers, params);
	return (0);
}
