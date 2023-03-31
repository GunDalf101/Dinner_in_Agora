/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:24:54 by mbennani          #+#    #+#             */
/*   Updated: 2023/02/15 11:44:26 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	timer(t_time *time)
{
	gettimeofday(&(time->timer), NULL);
	time->currenttime = (time->timer.tv_sec * 1000) + (time->timer.tv_usec
			/ 1000);
	return(time->currenttime - time->timeorigin);
}

void	sleeper(t_time *time, size_t how_much_to_sleep)
{
	size_t	starting_time;
	starting_time = timer(time);
	while (timer(time) - starting_time <= how_much_to_sleep)
		usleep(100);
}