/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djmekki < djmekki@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 11:20:29 by djmekki           #+#    #+#             */
/*   Updated: 2022/12/31 23:19:12 by djmekki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	**philos;
	t_data	*data;
	int		i;

	chck_arg(ac, &av[1]);
	i = 0;
	data = parse_data(&av[1]);
	philos = init_philo(data);
	init_mutex(data);
	while (i < data->n_of_philo)
	{
		pthread_create(&philos[i]->thread, NULL,
			(void *)routine, (void *)philos[i]);
		i++;
	}
	while (!chck_philo(philos, data))
		ms_sleep(1);
	i = 0;
	while (i < data->n_of_philo)
		pthread_join(philos[i++]->thread, NULL);
	free_philos(philos);
	free_data(data);
	return (0);
}
