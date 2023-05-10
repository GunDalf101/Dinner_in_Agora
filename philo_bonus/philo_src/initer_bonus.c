/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initer_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:46:38 by mbennani          #+#    #+#             */
/*   Updated: 2023/04/07 14:48:44 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	fork_sema(t_table *table)
{
	int	i;

	i = 0;
	sem_unlink("/fourchette");
	sem_unlink("/printer");
	sem_unlink("/locker");
	table->printer = sem_open("/printer", 1, O_CREAT | O_EXCL, 0777);
	table->locker = sem_open("/locker", 1, O_CREAT | O_EXCL, 0777);
	table->dafork = sem_open("/fourchette", table->philo_num, O_CREAT | O_EXCL, 0777);
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
	int pid;

	i = 0;
	table->philos = malloc(table->philo_num * sizeof(t_philosopher));
	philo_assigner(table);
	if (!table->philos)
		error_thrower(1);
	while (i < table->philo_num)
	{
		pid = fork();
		if (pid == 0)
			philosophizing(table->philos[i]);
		else
			table->philos[i]->pid = pid;
		i++;
	}
}
