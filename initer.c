/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:46:38 by mbennani          #+#    #+#             */
/*   Updated: 2023/02/15 12:19:21 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosophizing(t_philosopher *philo)
{
	int	i;

	i = 0;
	while (1)
	{
		if (philo->left_fork->state == AVAILABLE && philo->right_fork->state == AVAILABLE)
		{
			pthread_mutex_lock(&(philo->left_fork->dafork));
			pthread_mutex_lock(&(philo->right_fork->dafork));
			philo->left_fork->state = UNAVAILABLE;
			philo->right_fork->state = UNAVAILABLE;
			philo->state = EATING;
		}
		if (philo->state == EATING)
		{
			timer(&(philo->watch));
			printf(" philosopher %d is eating\n",
					philo->id);
			usleep(60 * 1000);
			philo->state = STARVING;
			philo->left_fork->state = AVAILABLE;
			philo->right_fork->state = AVAILABLE;
			pthread_mutex_unlock(&(philo->left_fork->dafork));
			pthread_mutex_unlock(&(philo->right_fork->dafork));
		}
		else if (philo->state == SLEEPING)
		{
			timer(&(philo->watch));
			printf(" philosopher %d is sleeping\n",
					philo->id);
			usleep(60 * 1000);
		}
		else if (philo->state == THINKING)
		{
			timer(&(philo->watch));
			printf(" philosopher %d is thinking\n",
					philo->id);
			usleep(60 * 1000);
		}
		if (philo->state == STARVING)
		{
			timer(&(philo->watch));
			printf(" philosopher %d died\n",
					philo->id);
			return (SUCCESS);
		}
	}
	return (FAILURE);
}

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
		pthread_mutex_init(&(table->forks[i]->dafork), NULL);
		if (!table->forks[i])
			error_thrower(1);
		table->forks[i]->state = AVAILABLE;
		table->forks[i]->id = i + 1;
		i++;
	}
}

void	philo_thread(t_table *table)
{
	int i;
	int rc;

	i = 0;
	table->philos = malloc(table->philo_num * sizeof(t_philosopher));
	if (!table->philos)
		error_thrower(1);
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
		rc = pthread_create(&(table->philos[i]->philo), NULL,
				(void *)philosophizing, table->philos[i]);
		if (rc)
			error_thrower(1);
		i++;
	}
}
