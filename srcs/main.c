/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:27:46 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/23 14:40:32 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int ac, char **av)
{

	if (ac < 5 || ac > 6)
	{
		write(2, "Wrong numbers of arguments\n", 27);
		return (0);
	}
	if (check_args(ac - 1, av + 1) == -1)
		return (-1);
//	args = get_args(ac - 1, av + 1);
//	init_threads();
//	join_threads();
	return (0);
}
