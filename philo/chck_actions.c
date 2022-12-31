/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chck_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 07:40:13 by djmekki           #+#    #+#             */
/*   Updated: 2022/12/31 19:47:26 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	chck_death(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->data->death);
	result = philo->data->stop_s;
	pthread_mutex_unlock(&philo->data->death);
	return (result);
}

int	chck_meals(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->data->meals);
	result = philo->meals;
	pthread_mutex_unlock(&philo->data->meals);
	return (result);
}

unsigned long	chck_last_meal(t_philo *philo)
{
	long long	result;

	pthread_mutex_lock(&philo->data->last);
	result = philo->last_eat;
	pthread_mutex_unlock(&philo->data->last);
	return (result);
}

int	chck_philo(t_philo **philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_of_philo)
	{
		if (chck_last_meal(philo[i]) != 0
			&& current_timestamp() - chck_last_meal(philo[i]) > data->t_die)
		{
			die(philo[i]);
			return (1);
		}
		if (!philo[i]->finished && chck_meals(philo[i]) == data->n_must_eat
			&& ++data->philo_ate)
				++philo[i]->finished;
		if (data->philo_ate == data->n_of_philo)
		{
			death(philo[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
