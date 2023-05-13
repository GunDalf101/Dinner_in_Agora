/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennani <mbennani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:29:18 by mbennani          #+#    #+#             */
/*   Updated: 2023/05/13 16:16:56 by mbennani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <pthread.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <fcntl.h>

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

typedef struct s_time
{
	struct timeval	timer;
	long long		timeorigin;
	long long		currenttime;
}					t_time;

struct s_philosopher
{
	int				id;
	pthread_t		philo;
	int				pid;
	int				state;
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
	sem_t			*dafork;
	sem_t			*printer;
	sem_t			*locker;
	int				philo_num;
	int				life_time;
	int				eatin_time;
	int				sleepin_time;
	int				isded;
	size_t			starvin_time;
	int				currentphil;
	t_time			clock;
};

int					ft_atoi(const char *str);
void				error_thrower(int err);
void				fork_sema(t_table *table);
void				philo_proc(t_table *table);
size_t				timer(t_time *time);
void				sleeper(t_time *time, size_t how_much_to_sleep, \
t_philosopher *philo);
int					supremeruler(t_table *table);
int					philosophizing(t_philosopher *philo);
int					death(t_table *table, size_t time_origin, int id);
void				philo_thread(t_table *table);
void				free_philo(t_table *table);
int					killemall(t_table *table);

#endif