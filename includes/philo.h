/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:41:52 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/16 12:55:52 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_args{
	int	*tab;
	int	args_nb;
}	t_args;

/*	args_functions.c	*/

int		check_args(int ac, char **av);
t_args	*get_args(int ac, char **av);

/*	utils.c				*/

int	ft_atoi(const char *nptr);
size_t	ft_strlen(const char *s);

/*	free_functions.c	*/

void	free_args(t_args *args);

#endif
