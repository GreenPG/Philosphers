/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:41:52 by gpasquet          #+#    #+#             */
/*   Updated: 2023/03/10 15:13:35 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum e_state {start ,sleeping, thinking, eating, dead, take}	t_state;

typedef struct s_forks {
	int				philo_nb;
	pthread_mutex_t	*tab;
}	t_forks;

typedef struct s_philo {
	int				id;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nb_eat;
	int				finish;
	pthread_mutex_t	time_mut;
	t_state			state;
	pthread_mutex_t	*forks[2];
}	t_philo;

/*	main.c	*/

/*	args_functions.c	*/

t_forks			*init_forks(char *input);
t_philo			**init_philos(char **av, int ac, t_forks *forks);

/* 	forks.c		*/

t_forks			*init_forks(char *input);

/*	check_args.c	*/

int				check_args(int ac, char **av);

/*	life.c			*/

void			life_loop(t_philo *ph_data, long int current_time,
					long int last_eat_t);

/*	utils.c				*/

int				ft_atoi(const char *nptr);
size_t			ft_strlen(const char *s);
long long		get_set_time(int par, t_philo *ph_data);
void			change_status(enum e_state status, t_philo *data, long int time);

/*	free_functions.c	*/

void			free_forks(t_forks **forks);
void			free_philos(t_philo ***philos, int nb_philo);

#endif
