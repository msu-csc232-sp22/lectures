/**
 * CSC232 - Data Structures
 * Missouri State University, Spring 2022
 *
 * @file    test.cpp
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 * @brief   Unit tests.
 * @version 0.2021.11.21
 * @date    2021-11-21
 *
 * @copyright Copyright (c) 2021 James R. Daehn
 */

#include <gtest/gtest.h>

TEST(HelloTest, BasicAssertions)
{
	EXPECT_STRNE("hello", "world");
	EXPECT_EQ(7 * 6, 42);
}
