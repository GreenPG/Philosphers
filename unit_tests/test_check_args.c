/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_check_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:41:42 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/22 15:55:01 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../greatest/greatest.h"
#include <philo.h>

TEST	only_digits(void)
{
	char	*args1[5] = {"432", "323", "3123", "321", NULL};
	char	*args2[5] = {"432", "323", "3123", "321", "432534"};
	char	*args3[5] = {"432", "323", NULL, "321", "432534"};

	ASSERT_EQ_FMT(0, check_args(4, args1), "%i");
	ASSERT_EQ_FMT(0, check_args(5, args2), "%i");
	ASSERT_EQ_FMT(-1, check_args(5, args3), "%i");
	PASS();
}

TEST	only_nondigits(void)
{
	char	*args4[5] = {"fdsdf", "fdsdf", "fdsdf", "fdsdf", NULL};
	char	*args5[5] = {"fdsdf", "fdsdf", "fdsdf", "fdsdf", "fdsdf"};
	char	*args6[5] = {"=+/fdsdf", "fdsdf", "fdsdf", "fdsdf", "fdsdf"};

	ASSERT_EQ(-1, check_args(4, args4));
	ASSERT_EQ(-1, check_args(5, args5));
	ASSERT_EQ(-1, check_args(5, args6));
	PASS();
}

TEST	digits_and_nondigits(void)
{
	char	*args7[5] = {"dsa432", "323", "3123", "321", "432534"};
	char	*args8[5] = {"432", "fd323", "3123", "321", "432534"};
	char	*args9[5] = {"432", "dsa323", NULL, "321", "432534"};

	ASSERT_EQ(-1, check_args(4, args7));
	ASSERT_EQ(-1, check_args(5, args8));
	ASSERT_EQ(-1, check_args(5, args9));
	PASS();
}

TEST	wrong_ac(void)
{
	char	*args10[5] = {"432", "323", "3123", "321", NULL};
	char	*args11[5] = {"dsa432", "323", "3123", "321", "432534"};
	char	*args12[5] = {"432", "323", "3123", "321", "432534"};
	char	*args13[5] = {"432", "323", NULL, "321", "432534"};

	ASSERT_EQ(-1, check_args(5, args10));
	ASSERT_EQ(-1, check_args(2, args11));
	ASSERT_EQ(-1, check_args(6, args12));
	ASSERT_EQ(-1, check_args(4, args13));
	PASS();
}

TEST	long_input(void)
{
	char	*input0[4] = {"4", "1000", "300", "500"};
	char	*input1[4] = {"4000000000000000000", "1000", "300", "500"};
	char	*input2[4] = {"4", "100000000000000000", "300", "500"};
	char	*input3[4] = {"4", "1000", "300000000000000000", "500"};
	char	*input4[4] = {"4", "1000", "300", "50000000000000000000"};
	char	*input5[5] = {"4", "1000", "300", "500", "1000000000000000000"};

	ASSERT_EQ_FMT(0, check_args(4, input0), "%i");
	ASSERT_EQ_FMT(-1, check_args(4, input1), "%i");
	ASSERT_EQ_FMT(-1, check_args(4, input2), "%i");
	ASSERT_EQ_FMT(-1, check_args(4, input3), "%i");
	ASSERT_EQ_FMT(-1, check_args(4, input4), "%i");
	ASSERT_EQ_FMT(-1, check_args(5, input5), "%i");
	PASS();
}

TEST	negative_input(void)
{
	char	*input1[4] = {"-4", "1000", "300", "500"};
	char	*input2[4] = {"4", "-1000", "300", "500"};
	char	*input3[4] = {"4", "1000", "-300", "500"};
	char	*input4[4] = {"4", "1000", "300", "-500"};
	char	*input5[5] = {"4", "1000", "300", "500", "-10"};

	ASSERT_EQ_FMT(-1, check_args(4, input1), "%i");
	ASSERT_EQ_FMT(-1, check_args(4, input2), "%i");
	ASSERT_EQ_FMT(-1, check_args(4, input3), "%i");
	ASSERT_EQ_FMT(-1, check_args(4, input4), "%i");
	ASSERT_EQ_FMT(-1, check_args(5, input5), "%i");
	PASS();
}

SUITE(check_args_suite) {
	RUN_TEST(only_digits);
	RUN_TEST(only_nondigits);
	RUN_TEST(digits_and_nondigits);
	RUN_TEST(wrong_ac);
	RUN_TEST(long_input);
	RUN_TEST(negative_input);
}
