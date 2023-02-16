/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:39:15 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/16 12:57:03 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include "../greatest/greatest.h"

///////////////////////////////////////////////////////////////////////////////
/// ASSERTIONS

TEST	ASSERT_ARGS_EQ(t_args const *actual, int const *expected, int size)
{
	for (int i = 0; i < size; i++)
	{
		ASSERT_EQ_FMT(actual->tab[i], expected[i], "%i");
	}
	PASS();

}
///////////////////////////////////////////////////////////////////////////////
///	TESTS
//

TEST	simple_input(void)
{
	char	*input1[4] = {"4", "1000", "300", "500"};
	char	*input2[5] = {"4", "1000", "300", "500", "10"};
	t_args	*args;

	args = get_args(4, input1);
	CHECK_CALL(ASSERT_ARGS_EQ(args, (int[]){4, 1000, 300, 500}, 4));
	free_args(args);
	args = get_args(5, input2);
	CHECK_CALL(ASSERT_ARGS_EQ(args, (int[]){4, 1000, 300, 500, 10}, 5));
	free_args(args);
	PASS();
}

TEST	negative_input(void)
{
	char	*input1[4] = {"-4", "1000", "300", "500"};
	char	*input2[4] = {"4", "-1000", "300", "500"};
	char	*input3[4] = {"4", "1000", "-300", "500"};
	char	*input4[4] = {"4", "1000", "300", "-500"};
	char	*input5[5] = {"4", "1000", "300", "500", "-10"};
	t_args	*args;

	args = get_args(4, input1);
	ASSERT_EQ(NULL, args);
	free(args);
	args = get_args(4, input2);
	ASSERT_EQ(NULL, args);
	free(args);
	args = get_args(4, input3);
	ASSERT_EQ(NULL, args);
	free(args);
	args = get_args(4, input4);
	ASSERT_EQ(NULL, args);
	free(args);
	args = get_args(5, input5);
	ASSERT_EQ(NULL, args);
	PASS();
}

SUITE(get_args_suite) {
	RUN_TEST(simple_input);
	RUN_TEST(negative_input);
}
