/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_threads_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:43:29 by mbennani          #+#    #+#             */
/*   Updated: 2023/05/13 16:16:25 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	killemall(t_table *table)
{
	int	i;
	int	status;

	i = 0;
	while (waitpid(-1, &status, 0) != -1)
	{
		if (status == SUCCESS)
		{
			while (i < table->philo_num)
			{
				kill(table->philos[i]->pid, 9);
				i++;
			}
			return (SUCCESS);
		}
	}
	return (FAILURE);
}
