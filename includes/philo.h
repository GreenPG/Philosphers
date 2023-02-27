/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:41:52 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/27 14:28:29 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum e_state {start ,sleeping, thinking, eating, dead}	t_state;

typedef struct s_forks {
	int	philo_nb;
	int	*tab;
}	t_forks;

typedef struct s_philo {
	int		id;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		nb_eat;
	t_state	state;
	t_forks	*forks;
}	t_philo;

/*	args_functions.c	*/

t_forks			*init_forks(char *input);
t_philo			**init_philos(char **av, int ac);

/*	check_args.c	*/

int				check_args(int ac, char **av);

/*	utils.c				*/

int				ft_atoi(const char *nptr);
size_t			ft_strlen(const char *s);
struct timeval	get_set_starttime(int par);

/*	free_functions.c	*/

void			free_forks(t_forks **forks);
void			free_philos(t_philo ***philos);

#endif
