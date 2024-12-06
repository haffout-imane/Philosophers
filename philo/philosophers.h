/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihaffout <ihaffout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 04:45:47 by ihaffout          #+#    #+#             */
/*   Updated: 2024/06/26 17:54:39 by ihaffout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_parameters
{
	int				eat_limit;
	int				num_philo;
	long long		time_die;
	long long		time_eat;
	long long		time_sleep;
	long long		start_simulation;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	mutex;
}					t_parameters;

typedef struct s_philosophere
{
	int				id;
	int				full;
	int				meals_eaten;
	long long		last_meal_time;
	t_parameters	*params;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
}					t_philosopher;

//----------------------- ERRORS -----------------------//
int					print_error(char *str);
int					ft_detach(int option, int index, t_parameters *params,
						t_philosopher *philosophers);

//----------------------- CHECKS -----------------------//
int					check_limit(t_philosopher *philosopher);
int					check_dead(t_philosopher *philosopher);
int					death_checker(t_philosopher *philosophers);
void				check_full(t_philosopher *philosopher);

//----------------------- UTILS -----------------------//
int					ft_atoi(const char *str);
long long			current_time(void);

//----------------------- INITIALIZATION -----------------------//
int					forks_init(t_parameters *params);
int					init_mutexes(t_parameters *params);
int					parse_parameters(int ac, char **av, t_parameters *params);
int					philosophers_init(t_philosopher *philosophers,
						t_parameters *params);
int					init_all(t_parameters *params, t_philosopher *philosophers);

//----------------------- LIFECIRCLE -----------------------//
void				*lifecircle(void *philo);
void				sleeping(t_philosopher *philosopher);
void				thinking(t_philosopher *philosopher);
void				eating(t_philosopher *philosopher);

//----------------------- philosophers -----------------------//
int					run_simulation(t_philosopher *philosophers,
						t_parameters *params);
int					exit_simulation(t_parameters *params,
						t_philosopher *philosophers, int return_value);
#endif