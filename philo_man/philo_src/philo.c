/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:29:07 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/19 14:46:38 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parsedshit(char **av, t_table *table)
{
	table->philo_num = ft_atoi(av[1]);
	if (table->philo_num == FAILURE)
		return (FAILURE);
	table->starvin_time = ft_atoi(av[2]);
	if (table->starvin_time == FAILURE)
		return (FAILURE);
	table->eatin_time = ft_atoi(av[3]);
	if (table->eatin_time == FAILURE)
		return (FAILURE);
	table->sleepin_time = ft_atoi(av[4]);
	if (table->sleepin_time == FAILURE)
		return (FAILURE);
	table->life_time = -1;
	if (av[5])
		table->life_time = ft_atoi(av[5]);
	if (fork_mutex(table) == FAILURE)
		return (FAILURE);
	pthread_mutex_init(&(table->printlock), NULL);
	pthread_mutex_init(&(table->locker), NULL);
	if (philo_thread(table) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	t_table	table;

	gettimeofday(&(table.clock.timer), NULL);
	table.clock.timeorigin = (table.clock.timer.tv_sec * 1000)
		+ (table.clock.timer.tv_usec / 1000);
	if (ac != 5 && ac != 6)
		return (error_thrower(0));
	if (parsedshit(av, &table) == FAILURE)
		return (FAILURE);
	while (1)
	{
		if (supremeruler(&table) == FAILURE)
			return (SUCCESS);
		usleep(5000);
	}
}
