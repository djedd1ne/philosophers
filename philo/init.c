/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 22:34:28 by djmekki           #+#    #+#             */
/*   Updated: 2022/12/31 21:37:34 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*parse_data(char **argv)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	data->n_of_philo = ft_atoi(*argv++);
	data->t_die = ft_atoi(*argv++);
	data->t_eat = ft_atoi(*argv++);
	data->t_sleep = ft_atoi(*argv++);
	if (*argv)
		data->n_must_eat = ft_atoi(*argv);
	else
		data->n_must_eat = -1;
	data->philo_ate = 0;
	data->stop_s = 0;
	return (data);
}

t_philo	**init_philo(t_data *data)
{
	t_philo	**philos;
	int		i;

	philos = (t_philo **)malloc(sizeof(t_philo *) * (data->n_of_philo));
	philos[data->n_of_philo] = NULL;
	i = 0;
	while (i < (data->n_of_philo))
	{
		philos[i] = (t_philo *)malloc(sizeof(t_philo));
		philos[i]->n = i + 1;
		philos[i]->data = data;
		philos[i]->meals = 0;
		philos[i]->finished = 0;
		philos[i]->fork_r = i;
		philos[i]->fork_l = (i + 1) % (data->n_of_philo);
		i++;
	}
	return (philos);
}

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks = (pthread_mutex_t *)malloc(sizeof(*data->forks) \
		* (data->n_of_philo));
	while (i < data->n_of_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->last, NULL);
	pthread_mutex_init(&data->death, NULL);
	pthread_mutex_init(&data->meals, NULL);
}
