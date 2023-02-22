/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:29:18 by mbennani          #+#    #+#             */
/*   Updated: 2023/02/15 11:44:24 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

enum				e_philostate
{
	THINKING,
	EATING,
	SLEEPING,
	STARVING
};

enum				e_forkstate
{
	UNAVAILABLE,
	AVAILABLE
};

enum				e_bool
{
	FALSE,
	TRUE
};

enum				e_rval
{
	SUCCESS,
	FAILURE
};

typedef struct s_fork
{
	int				id;
	int				state;
	pthread_mutex_t	dafork;
}					t_fork;

typedef struct s_time
{
	struct timeval	timer;
	long long		timeorigin;
	long long		currenttime;
}					t_time;

typedef struct s_philosopher
{
	int				id;
	int				state;
	pthread_t		philo;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_time			watch;
}					t_philosopher;

typedef struct s_table
{
	t_philosopher	**philos;
	t_fork			**forks;
	int				philo_num;
	int				life_time;
	int				eatin_time;
	int				sleepin_time;
	int				starvin_time;
	int				currentphil;
	t_time			clock;
}					t_table;

int					ft_atoi(const char *str);
void				error_thrower(int err);
void				fork_mutex(t_table *table);
void				philo_thread(t_table *table);
void				timer(t_time *time);

#endif