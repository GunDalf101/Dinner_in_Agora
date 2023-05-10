/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorhandle_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:49:00 by mbennani          #+#    #+#             */
/*   Updated: 2023/04/07 13:27:17 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	error_thrower(int err)
{
	if (err == 0)
		printf("Error code 0: Wrong argument count\n");
	else if (err == 1)
		printf("Error code 1: Failed allocation\n");
	exit(FAILURE);
}