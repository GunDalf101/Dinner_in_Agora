/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:46:38 by mbennani          #+#    #+#             */
/*   Updated: 2023/04/05 03:38:00 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fork_mutex(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(table->philo_num * sizeof(t_fork));
	if (!table->forks)
		error_thrower(1);
	while (i < table->philo_num)
	{
		table->forks[i] = malloc(sizeof(t_fork));
		if (!table->forks[i])
			error_thrower(1);
		pthread_mutex_init(&(table->forks[i]->dafork), NULL);
		table->forks[i]->state = AVAILABLE;
		table->forks[i]->id = i + 1;
		i++;
	}
}

void	philo_assigner(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		table->philos[i] = malloc(sizeof(t_philosopher));
		if (!table->philos[i])
			error_thrower(1);
		table->philos[i]->id = i + 1;
		if (i == 0)
			table->philos[i]->left_fork = table->forks[table->philo_num - 1];
		else
			table->philos[i]->left_fork = table->forks[i - 1];
		table->philos[i]->right_fork = table->forks[i];
		table->philos[i]->watch = table->clock;
		table->philos[i]->state = -1;
		table->philos[i]->meals = 0;
		table->philos[i]->latest_meal = 0;
		table->philos[i]->sleepin_time = table->sleepin_time;
		table->philos[i]->eatin_time = table->eatin_time;
		table->philos[i]->table = table;
		i++;
	}
}

void	philo_thread(t_table *table)
{
	int i;
	int rc;

	i = 0;
	table->philos = malloc(table->philo_num * sizeof(t_philosopher));
	philo_assigner(table);
	if (!table->philos)
		error_thrower(1);
	while (i < table->philo_num)
	{
		rc = pthread_create(&(table->philos[i]->philo), NULL,
				(void *)philosophizing, table->philos[i]);
		if (rc)
			error_thrower(1);
		pthread_detach(table->philos[i]->philo);
		i++;
	}
}
