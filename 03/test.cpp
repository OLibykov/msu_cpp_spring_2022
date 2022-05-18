#include <gtest/gtest.h>
#include "My_Matrix.hpp"

class MyTest : public ::testing::Test
{
protected:
    void SetUp()
    {
    }
    void TearDown()
    {
    }
};

TEST_F(MyTest, test_get_n_row_col)
{
	Matrix m(5, 3);
	ASSERT_EQ(m.get_n_row(), 5);
	ASSERT_EQ(m.get_n_col(), 3);
	Matrix m1(4, 4);
	ASSERT_EQ(m1.get_n_row(), 4);
	ASSERT_EQ(m1.get_n_col(), 4);
	m1 = Matrix(1, 1);
	ASSERT_EQ(m1.get_n_row(), 1);
	ASSERT_EQ(m1.get_n_col(), 1);
	m1 = m;
	ASSERT_EQ(m1.get_n_row(), 5);
	ASSERT_EQ(m1.get_n_col(), 3);
	m1 *= 3;
	ASSERT_EQ(m1.get_n_row(), 5);
	ASSERT_EQ(m1.get_n_col(), 3);
	Matrix m2(m1);
	Matrix m3(m1 + m2);
	ASSERT_EQ((m1 + m2).get_n_row(), 5);
	ASSERT_EQ((m1 + m2).get_n_col(), 3);
	ASSERT_EQ(m3.get_n_row(), 5);
	ASSERT_EQ(m3.get_n_col(), 3);
}

TEST_F(MyTest, test_taking_an_element)
{
	Matrix m(5, 3);
	for (size_t i = 0; i < 5; i++){
		for (size_t j = 0; j < 3; j++){
			m[i][j] = 5 * i + j;
		}
	}
	for (size_t i = 0; i < 5; i++){
		for (size_t j = 0; j < 3; j++){
			ASSERT_EQ(m[i][j], 5 * i + j);
		}
	}
	m *= 2;
	for (size_t i = 0; i < 5; i++){
		for (size_t j = 0; j < 3; j++){
			ASSERT_EQ(m[i][j], 2*(5 * i + j));
		}
	}
	Matrix m1(4, 4);
	for (size_t i = 0; i < 4; i++){
		for (size_t j = 0; j < 4; j++){
			m1[i][j] = 5;
		}
	}
	m = m1;
	ASSERT_NO_THROW(m[3][3]);
	ASSERT_EQ(m[3][3], 5);
	ASSERT_THROW(m[4][0], std::out_of_range);
	for (size_t i = 0; i < 4; i++){
		for (size_t j = 0; j < 4; j++){
			ASSERT_EQ(m[i][j], 5);
			ASSERT_NO_THROW(m[i][j]);
		}
	}
	for (size_t i = 0; i < 5; i++){
		ASSERT_THROW(m[4][i], std::out_of_range);
	}
	for (size_t i = 0; i < 4; i++){
		ASSERT_THROW(m[i][4], std::out_of_range);
	}
	m[1][2] = 10;
	m[0][0] = m[1][2] + m[3][3];
	ASSERT_EQ(m[0][0], 15);
}

TEST_F(MyTest, test_operators)
{
	Matrix m(5, 3);
	for (size_t i = 0; i < 5; i++){
		for (size_t j = 0; j < 3; j++){
			m[i][j] = 5 * i + j;
		}
	}
	for (size_t i = 0; i < 5; i++){
		for (size_t j = 0; j < 3; j++){
			ASSERT_EQ(m[i][j], 5 * i + j);
		}
	}
	Matrix m1;
	m1 = m + m;
	for (size_t i = 0; i < 5; i++){
		for (size_t j = 0; j < 3; j++){
			ASSERT_EQ(m1[i][j], 2*(5 * i + j));
		}
	}
	ASSERT_TRUE(m1 != m);
	ASSERT_FALSE(m1 == m);
	ASSERT_TRUE(m1 == m + m);
	m*=3;
	ASSERT_FALSE(m1 == m);
	m = m + m1;
	for (size_t i = 0; i < 5; i++){
		for (size_t j = 0; j < 3; j++){
			ASSERT_EQ(m[i][j], 5*(5 * i + j));
		}
	}
}

TEST_F(MyTest, test_sequence)
{
	const size_t rows = 5;
	const size_t cols = 3;
	Matrix m(rows, cols);
	std::cout <<  m[0][0] << std::endl;
	std::cout << m << std::endl;
	ASSERT_EQ(m.get_n_row(), 5);
	ASSERT_EQ(m.get_n_col(), 3);
	m[1][2] = 5; 
	std::cout <<  m[4][1] << std::endl;
	m *= 3; 
	Matrix m1(rows, cols);
	if (m1 == m)
	{
	}
	Matrix m2 = m1 + m;
	std::cout << m2 << std::endl;
}

