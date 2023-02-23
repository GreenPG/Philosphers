/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:41:52 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/23 16:28:18 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>

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
	t_forks	*forks;
}	t_philo;

/*	args_functions.c	*/

int		check_args(int ac, char **av);
t_forks	*init_forks(char *input);
t_philo	**init_philos(char **av, int ac);

/*	utils.c				*/

int	ft_atoi(const char *nptr);
size_t	ft_strlen(const char *s);

/*	free_functions.c	*/


#endif
