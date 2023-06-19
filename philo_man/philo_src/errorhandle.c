/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorhandle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:49:00 by mbennani          #+#    #+#             */
/*   Updated: 2023/06/19 14:47:50 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_thrower(int err)
{
	if (err == 0)
		printf("Error code 0: Wrong argument count\n");
	else if (err == 1)
		printf("Error code 1: Failed allocation\n");
	else if (err == 2)
		printf("Error code 2: Unexpected character\n");
	else if (err == 3)
		printf("Error code 3: Argument overflow\n");
	return (FAILURE);
}
