/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ruler.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:10:25 by mbennani          #+#    #+#             */
/*   Updated: 2023/05/11 23:39:08 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	immortality(t_table *table)
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
	id = 0;
	while (id < table->philo_num)
	{
		pthread_join(table->philos[id]->philo, NULL);
		id++;
	}
	pthread_mutex_unlock(&table->locker);
	return (SUCCESS);
}

int	death(t_table *table, size_t time_origin, int id)
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
			pthread_join(table->philos[i]->philo, NULL);
			i++;
		}
		// pthread_mutex_unlock(&table->locker);
		return (SUCCESS);
	}
	pthread_mutex_unlock(&table->locker);
	return (FAILURE);
}

void	free_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		free(table->philos[i]);
		i++;
	}
	i = 0;
	while (i < table->philo_num)
	{
		pthread_mutex_destroy(&table->forks[i]->dafork);
		free(table->forks[i]);
		i++;
	}
}

int	supremeruler(t_table *table)
{
	int		i;
	size_t	time_origin;

	i = 0;
	time_origin = timer(&table->clock);
	if (immortality(table) == SUCCESS)
		return (free_philo(table), free(table->philos) \
		, free(table->forks), FAILURE);
	while (i < table->philo_num)
	{
		if (death(table, time_origin, i) == SUCCESS)
			return (free(table->philos), free(table->forks), FAILURE);
		i++;
	}
	return (SUCCESS);
}
