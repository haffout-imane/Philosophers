/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihaffout <ihaffout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 04:40:25 by ihaffout          #+#    #+#             */
/*   Updated: 2024/06/25 14:24:58 by ihaffout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	exit_simulation(t_parameters *params, t_philosopher *philosophers,
		int return_value)
{
	int	i;

	if (return_value == 0)
	{
		i = 0;
		while (i < params->num_philo)
			pthread_detach(philosophers[i++].thread);
	}
	i = 0;
	while (i < params->num_philo)
		pthread_mutex_destroy(&(params->forks[i++]));
	free(params->forks);
	pthread_mutex_destroy(&(params->write));
	pthread_mutex_destroy(&(params->mutex));
	free(params);
	free(philosophers);
	return (return_value);
}

int	run_simulation(t_philosopher *philosophers, t_parameters *params)
{
	int	i;

	i = 0;
	params->start_simulation = current_time();
	while (i < params->num_philo)
	{
		philosophers[i].last_meal_time = params->start_simulation;
		if (pthread_create(&(philosophers[i].thread), NULL, &lifecircle,
				&philosophers[i]))
			return (ft_detach(1, i, params, philosophers));
		i++;
		usleep(5);
	}
	return (0);
}

int	main(int ac, char **av)
{
	int				i;
	t_parameters	*params;
	t_philosopher	*philosophers;

	i = 0;
	params = malloc(sizeof(t_parameters));
	if (!params)
		return (print_error("Failed to allocate memory for parameters"));
	if (parse_parameters(ac, av, params))
		return (free(params), print_error("invalid parameters"));
	philosophers = malloc(sizeof(t_philosopher) * params->num_philo);
	if (!philosophers)
		return (free(params),
			print_error("Failed to allocate memory for philosophers"));
	if (init_all(params, philosophers))
	{
		free(params);
		free(philosophers);
		return (1);
	}
	if (run_simulation(philosophers, params))
		return (exit_simulation(params, philosophers, 1));
	death_checker(philosophers);
	return (exit_simulation(params, philosophers, 0));
}
