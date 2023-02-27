/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_init_philos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:40:33 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/27 14:28:52 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include "../greatest/greatest.h"

///////////////////////////////////////////////////////////////////////////////
/// ASSERTIONS

TEST	ASSERT_PHILOS_EQ(t_philo **actual, char **args, int size)
{
	int	pos = 0;
	int	i = 0;

	while (pos < size)
	{
		ASSERT_EQ_FMT(pos + 1, actual[pos]->id, "%i");
		ASSERT_EQ_FMT(ft_atoi(args[1]), actual[pos]->t_die, "%i");
		ASSERT_EQ_FMT(ft_atoi(args[2]), actual[pos]->t_eat, "%i");
		ASSERT_EQ_FMT(ft_atoi(args[3]), actual[pos]->t_sleep, "%i");
		ASSERT_EQ_FMT(start, actual[pos]->state, "%i");
		if (size == 5)
			ASSERT_EQ_FMT(ft_atoi(args[4]), actual[pos]->nb_eat, "%i");
		ASSERT_EQ_FMT(ft_atoi(args[0]), actual[pos]->forks->philo_nb, "%i");
		while (i < actual[pos]->forks->philo_nb)
		{
			ASSERT_EQ_FMT(0, actual[pos]->forks->tab[i], "%i");
			i++;
		}
		pos++;
	}
	free_philos(&actual);
	PASS();
}
///////////////////////////////////////////////////////////////////////////////
///	TESTS

TEST	simple_input(void)
{
	char	*args1[4] = {"4", "323", "3123", "321"};
	char	*args2[5] = {"4", "323", "3123", "321", "43"};

	CHECK_CALL(ASSERT_PHILOS_EQ(init_philos(args1, 4), args1, 4));
	CHECK_CALL(ASSERT_PHILOS_EQ(init_philos(args2, 5), args2, 4));
	PASS();
}
///////////////////////////////////////////////////////////////////////////////
///	SUITE

SUITE(init_philos_suite) {
	RUN_TEST(simple_input);
}
