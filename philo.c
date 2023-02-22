/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:29:07 by mbennani          #+#    #+#             */
/*   Updated: 2023/02/15 12:05:32 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	mutex;

int	supremeruler(t_table *table)
{
	int	i;
	int	d;

	i = 0;
	d = rand();
	printf("%d\n", d);
	if (d < 10000)
	{
		while (i < table->philo_num)
		{
			table->philos[i]->state = STARVING;
			usleep(1000);
			i++;
		}
		return (SUCCESS);
	}
	return (FAILURE);
}

void	parsedshit(char **av, t_table *table)
{
	table->philo_num = ft_atoi(av[1]);
	table->starvin_time = ft_atoi(av[2]);
	table->eatin_time = ft_atoi(av[3]);
	table->sleepin_time = ft_atoi(av[4]);
	if (av[5])
		table->life_time = ft_atoi(av[5]);
	fork_mutex(table);
	philo_thread(table);
}

int	main(int ac, char **av)
{
	t_table	table;
	int		i;

	gettimeofday(&(table.clock.timer), NULL);
	table.clock.timeorigin = (table.clock.timer.tv_sec * 1000)
		+ (table.clock.timer.tv_usec / 1000);
	if (ac != 5 && ac != 6)
		error_thrower(0);
	parsedshit(av, &table);
	// while (1)
	// {
	// 	if (supremeruler(&table) == 0)
	// 		break ;
	// }
	i = 0;
	while (i < table.philo_num)
	{
		pthread_join(table.philos[i]->philo, NULL);
		i++;
	}
}
