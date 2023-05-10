/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorhandle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:49:00 by mbennani          #+#    #+#             */
/*   Updated: 2023/05/08 22:56:23 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_thrower(int err)
{
	if (err == 0)
		printf("Error code 0: Wrong argument count\n");
	else if (err == 1)
		printf("Error code 1: Failed allocation\n");
	exit(FAILURE);
}
