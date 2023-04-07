/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boring_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 01:44:32 by mbennani          #+#    #+#             */
/*   Updated: 2023/04/05 02:41:57 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine_helper(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->table->printlock);
	printf("%lu ms %d is sleeping\n", timer(&philo->watch), philo->id);
	pthread_mutex_unlock(&philo->table->printlock);
	sleeper(&philo->watch, philo->sleepin_time);
	pthread_mutex_lock(&philo->table->printlock);
	printf("%lu ms %d is thinking\n", timer(&philo->watch), philo->id);
	pthread_mutex_unlock(&philo->table->printlock);
}

int	philosophizing(t_philosopher *philo)
{
	if (philo->id % 2 == 1)
		sleeper(&philo->watch, 50);
	while (1)
	{
		pthread_mutex_lock(&philo->right_fork->dafork);
		pthread_mutex_lock(&philo->table->printlock);
		printf("%lu ms %d has taken a fork\n", timer(&philo->watch), philo->id);
		pthread_mutex_unlock(&philo->table->printlock);
		pthread_mutex_lock(&philo->left_fork->dafork);
		pthread_mutex_lock(&philo->table->printlock);
		printf("%lu ms %d has taken a fork\n", timer(&philo->watch), philo->id);
		printf("%lu ms %d is eating\n", timer(&philo->watch), philo->id);
		pthread_mutex_unlock(&philo->table->printlock);
		pthread_mutex_lock(&philo->table->locker);
		philo->latest_meal = timer(&philo->watch);
		philo->meals++;
		pthread_mutex_unlock(&philo->table->locker);
		sleeper(&philo->watch, philo->eatin_time);
		pthread_mutex_unlock(&philo->right_fork->dafork);
		pthread_mutex_unlock(&philo->left_fork->dafork);
		if (philo->meals == philo->table->life_time)
			break ;
		routine_helper(philo);
	}
	return (FAILURE);
}