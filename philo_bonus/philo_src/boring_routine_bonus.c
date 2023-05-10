/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boring_routine_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 01:44:32 by mbennani          #+#    #+#             */
/*   Updated: 2023/05/09 18:37:32 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	if (philo->id % 2 == 1)
		sleeper(&philo->watch, 50, philo);
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
		philo->latest_meal = timer(&philo->watch);
		philo->meals++;
		sem_post(philo->table->locker);
		sleeper(&philo->watch, philo->eatin_time, philo);
		sem_post(philo->table->dafork);
		sem_post(philo->table->dafork);
		if (philo->meals == philo->table->life_time)
			break ;
		routine_helper(philo);
	}
	return (FAILURE);
}
