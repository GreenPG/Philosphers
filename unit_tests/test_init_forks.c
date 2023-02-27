/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_init_forks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:21:20 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/25 16:01:01 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include "../greatest/greatest.h"

///////////////////////////////////////////////////////////////////////////////
/// ASSERTIONS

TEST	ASSERT_FORKS_EQ(t_forks *actual, t_forks *expected, int size)
{
	int i = 0;

	ASSERT_EQ_FMT(actual->philo_nb, expected->philo_nb, "%i");
	while (i < size)
	{
		ASSERT_EQ_FMT(actual->tab[i], 0, "%i");
		i++;
	}
	free_forks(&actual);
	PASS();
}

///////////////////////////////////////////////////////////////////////////////
///	TESTS

TEST	simple_input(void)
{
	char	*ipt1 = "4";
	char	*ipt2 = "1";
	char	*ipt3 = "0";
	char	*ipt4 = "-4";
	t_forks	exp1 = {.philo_nb = 4};
	t_forks	exp2 = {.philo_nb = 1};

	CHECK_CALL(ASSERT_FORKS_EQ(init_forks(ipt1), &exp1, 4));
	CHECK_CALL(ASSERT_FORKS_EQ(init_forks(ipt2), &exp2, 1));
	ASSERT_EQ_FMT(NULL, init_forks(ipt3), "%p");
	ASSERT_EQ_FMT(NULL, init_forks(ipt4), "%p");
	ASSERT_EQ_FMT(NULL, init_forks(NULL), "%p");
	PASS();
}
///////////////////////////////////////////////////////////////////////////////
///	SUITE

SUITE(init_forks_suite) {
	RUN_TEST(simple_input);
}
