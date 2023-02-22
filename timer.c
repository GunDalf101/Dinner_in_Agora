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

void	timer(t_time *time)
{
	gettimeofday(&(time->timer), NULL);
	time->currenttime = (time->timer.tv_sec * 1000) + (time->timer.tv_usec
			/ 1000);
	printf("%lld ms", time->currenttime - time->timeorigin);
}
