/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ruler_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:10:25 by mbennani          #+#    #+#             */
/*   Updated: 2023/04/07 15:46:42 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int immortality(t_table *table)
{
	int	id;

	id = 0;
	sem_wait(table->locker);
	while (id < table->philo_num)
	{
		if (table->philos[id]->meals != table->life_time)
		{
			sem_post(table->locker);
			return (FAILURE);
		}
		id++;
	}
	sem_post(table->locker);
	return (SUCCESS);
}

int death(t_table *table, size_t time_origin, int id)
{
	int	i;

	i = 0;
	sem_wait(table->locker);
	if (time_origin - table->philos[id]->latest_meal > table->starvin_time)
	{
		sem_wait(table->printer);
		printf("%lu ms %d died\n", timer(&table->clock), id + 1);
		table->isded = TRUE;
		exit(1);
	}
	sem_post(table->locker);
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
}
