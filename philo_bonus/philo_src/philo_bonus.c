/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:29:07 by mbennani          #+#    #+#             */
/*   Updated: 2023/05/14 17:06:25 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	parsedshit(char **av, t_table *table)
{
	table->philo_num = ft_atoi(av[1]);
	table->starvin_time = ft_atoi(av[2]);
	table->eatin_time = ft_atoi(av[3]);
	table->sleepin_time = ft_atoi(av[4]);
	table->life_time = -1;
	if (av[5])
		table->life_time = ft_atoi(av[5]);
	fork_sema(table);
	philo_proc(table);
}

int	main(int ac, char **av)
{
	t_table	table;
	int		i;

	i = 0;
	gettimeofday(&(table.clock.timer), NULL);
	table.clock.timeorigin = (table.clock.timer.tv_sec * 1000)
		+ (table.clock.timer.tv_usec / 1000);
	if (ac != 5 && ac != 6)
		error_thrower(0);
	i = 0;
	parsedshit(av, &table);
	killemall (&table);
}
