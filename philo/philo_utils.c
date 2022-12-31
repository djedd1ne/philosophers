/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 23:46:59 by djmekki           #+#    #+#             */
/*   Updated: 2022/12/31 21:46:58 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	current_timestamp(void)
{
	unsigned long	millisecond;
	t_time			t;

	gettimeofday(&t, NULL);
	millisecond = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (millisecond);
}

void	ms_sleep(unsigned long time)
{
	unsigned long	t1;

	t1 = current_timestamp();
	while (current_timestamp() - t1 < time)
		usleep(100);
}

void	free_philos(t_philo **philos)
{
	t_philo	**head;

	head = philos;
	while (philos && *philos)
		free(*philos++);
	free (head);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	pthread_mutex_destroy(&data->death);
	pthread_mutex_destroy(&data->last);
	pthread_mutex_destroy(&data->meals);
	pthread_mutex_destroy(&data->print);
	free(data);
}
