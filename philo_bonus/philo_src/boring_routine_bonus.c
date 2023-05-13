/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boring_routine_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 01:44:32 by mbennani          #+#    #+#             */
/*   Updated: 2023/05/13 22:50:46 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	routine_firstcheck(t_philosopher *philo)
{
	if (philo->id % 2 == 1)
		sleeper(&philo->watch, 50, philo);
	if (philo->table->philo_num == 1)
	{
		printf("%lu ms %d has taken a fork\n", timer(&philo->watch), philo->id);
		sleeper (&philo->watch, philo->table->starvin_time, philo);
		printf("%lu ms %d died\n", timer(&philo->watch), philo->id);
		exit (0);
	}
}

void	routine_helper(t_philosopher *philo)
{
	sem_wait(philo->table->printer);
	printf("%lu ms %d is sleeping\n", timer(&philo->watch), philo->id);
	sem_post(philo->table->printer);
	sleeper(&philo->watch, philo->sleepin_time, philo);
	sem_wait(philo->table->printer);
	printf("%lu ms %d is thinking\n", timer(&philo->watch), philo->id);
	sem_post(philo->table->printer);
}

int	philosophizing(t_philosopher *philo)
{
	routine_firstcheck(philo);
	while (1)
	{
		sem_wait(philo->table->dafork);
		sem_wait(philo->table->printer);
		printf("%lu ms %d has taken a fork\n", timer(&philo->watch), philo->id);
		sem_post(philo->table->printer);
		sem_wait(philo->table->dafork);
		sem_wait(philo->table->printer);
		printf("%lu ms %d has taken a fork\n", timer(&philo->watch), philo->id);
		printf("%lu ms %d is eating\n", timer(&philo->watch), philo->id);
		sem_post(philo->table->printer);
		sem_wait(philo->table->locker);
		philo->meals++;
		sem_post(philo->table->locker);
		sleeper(&philo->watch, philo->eatin_time, philo);
		philo->latest_meal = timer(&philo->watch);
		sem_post(philo->table->dafork);
		sem_post(philo->table->dafork);
		if (philo->meals == philo->table->life_time)
			exit (SUCCESS);
		routine_helper(philo);
	}
	return (FAILURE);
}
