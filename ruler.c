/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:10:25 by mbennani          #+#    #+#             */
/*   Updated: 2023/02/15 11:44:17 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int immortality(t_table *table)
{
	int	id;

	id = 0;
	pthread_mutex_lock(&table->locker);
	while (id < table->philo_num)
	{
		if (table->philos[id]->meals != table->life_time)
		{
			pthread_mutex_unlock(&table->locker);
			return (FAILURE);
		}
		id++;
	}
	printf("Immortality achieved\n");
	id = 0;
	while (id < table->philo_num)
	{
		pthread_detach(table->philos[id]->philo);
		id++;
	}
	pthread_mutex_unlock(&table->locker);
	return (SUCCESS);
}

int death(t_table *table, size_t time_origin, int id)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->locker);
	if (time_origin - table->philos[id]->latest_meal > table->starvin_time)
	{
		pthread_mutex_lock(&table->printlock);
		printf("%lu ms %d died\n", timer(&table->clock), id + 1);
		while (i < table->philo_num)
		{
			pthread_detach(table->philos[i]->philo);
			i++;
		}
		pthread_mutex_unlock(&table->printlock);
		pthread_mutex_unlock(&table->locker);
		return (SUCCESS);
	}
	pthread_mutex_unlock(&table->locker);
	return (FAILURE);
}

int	supremeruler(t_table *table)
{
	int		i;
	size_t	time_origin;

	i = 0;
	time_origin = timer(&table->clock);
	if (immortality(table) == SUCCESS)
		return (FAILURE);
	while (i < table->philo_num)
	{
		if (death(table, time_origin, i) == SUCCESS)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
