/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:29:18 by mbennani          #+#    #+#             */
/*   Updated: 2023/05/11 19:49:17 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <unistd.h>

typedef struct s_philosopher	t_philosopher;
typedef struct s_table			t_table;

enum				e_philostate
{
	THINKING,
	EATING,
	NOTEATING,
	STARVING,
	FULL
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

struct s_philosopher
{
	int				id;
	int				state;
	pthread_t		philo;
	t_fork			*left_fork;
	t_fork			*right_fork;
	int				eatin_time;
	int				sleepin_time;
	t_time			watch;
	int				meals;
	size_t			latest_meal;
	t_table			*table;
};
struct s_table
{
	t_philosopher	**philos;
	t_fork			**forks;
	pthread_mutex_t	locker;
	pthread_mutex_t	printlock;
	int				philo_num;
	int				life_time;
	int				eatin_time;
	int				sleepin_time;
	size_t			starvin_time;
	int				currentphil;
	t_time			clock;
};

int					ft_atoi(const char *str);
void				error_thrower(int err);
void				fork_mutex(t_table *table);
void				philo_thread(t_table *table);
size_t				timer(t_time *time);
void				sleeper(t_time *time, size_t how_much_to_sleep);
int					supremeruler(t_table *table);
int					philosophizing(t_philosopher *philo);

#endif