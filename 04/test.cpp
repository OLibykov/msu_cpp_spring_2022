#include <gtest/gtest.h>
#include "BigInt.hpp"

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

TEST_F(MyTest, test_constructor_and_operator_equal_and_cout)
{
	std::string tmp;
	std::stringstream oss;
	
	BigInt a(123);
	oss << a << ' ';
	oss >> tmp;
	ASSERT_STREQ(tmp.c_str(), "123");
	
	BigInt a1("18446744073709551615");
	oss << a1 << ' ';
	oss >> tmp;
	ASSERT_STREQ(tmp.c_str(), "18446744073709551615");
	
	std::string s("743686428628622989392");
	BigInt a2(s);
	oss << a2 << ' ';
	oss >> tmp;
	ASSERT_STREQ(tmp.c_str(), s.c_str());
//конструктор копирования	
	BigInt a3(a1);
	oss << a1 << ' ';
	oss >> tmp;
	ASSERT_STREQ(tmp.c_str(), "18446744073709551615");
	oss << a3 << ' ';
	oss >> tmp;
	ASSERT_STREQ(tmp.c_str(), "18446744073709551615");
//конструктор перемещения
	BigInt a4(std::move(a2));
	oss << a2 << '_' << ' ';
	oss >> tmp;
	ASSERT_STREQ(tmp.c_str(), "_");
	oss << a4 << ' ';
	oss >> tmp;
	ASSERT_STREQ(tmp.c_str(), s.c_str());
//оператор копирования
	a2 = a3;
	oss << a2 << ' ';
	oss >> tmp;
	ASSERT_STREQ(tmp.c_str(), "18446744073709551615");
	oss << a3 << ' ';
	oss >> tmp;
	ASSERT_STREQ(tmp.c_str(), "18446744073709551615");
// оператор перемещения
	a1 = std::move(a4);
	oss << a4 << '_' << ' ';
	oss >> tmp;
	ASSERT_STREQ(tmp.c_str(), "_");
	oss << a1 << ' ';
	oss >> tmp;
	ASSERT_STREQ(tmp.c_str(), s.c_str());
}

TEST_F(MyTest, test_constructor_and_operator_equal_and_cout_negative)
{
	std::string tmp;
	std::stringstream oss;	
	BigInt a(-123);
	oss << a << ' ';
	oss >> tmp;
	ASSERT_STREQ(tmp.c_str(), "-123");
	
	BigInt a1("-18446744073709551615");
	oss << a1 << ' ';
	oss >> tmp;
	ASSERT_STREQ(tmp.c_str(), "-18446744073709551615");
	
	std::string s("-743686428628622989392");
	BigInt a2(s);
	oss << a2 << ' ';
	oss >> tmp;
	ASSERT_STREQ(tmp.c_str(), s.c_str());
//конструктор копирования	
	BigInt a3(a1);
	oss << a1 << ' ';
	oss >> tmp;
	ASSERT_STREQ(tmp.c_str(), "-18446744073709551615");
	oss << a3 << ' ';
	oss >> tmp;
	ASSERT_STREQ(tmp.c_str(), "-18446744073709551615");
//конструктор перемещения
	BigInt a4(std::move(a2));
	oss << a2 << '_' << ' ';
	oss >> tmp;
	ASSERT_STREQ(tmp.c_str(), "_");
	oss << a4 << ' ';
	oss >> tmp;
	ASSERT_STREQ(tmp.c_str(), s.c_str());
//оператор копирования
	a2 = a3;
	oss << a2 << ' ';
	oss >> tmp;
	ASSERT_STREQ(tmp.c_str(), "-18446744073709551615");
	oss << a3 << ' ';
	oss >> tmp;
	ASSERT_STREQ(tmp.c_str(), "-18446744073709551615");
// оператор перемещения
	a1 = std::move(a4);
	oss << a4 << '_' << ' ';
	oss >> tmp;
	ASSERT_STREQ(tmp.c_str(), "_");
	oss << a1 << ' ';
	oss >> tmp;
	ASSERT_STREQ(tmp.c_str(), s.c_str());
}

TEST_F(MyTest, test_compare)
{
	BigInt a1("18446744073709551615");
	BigInt a2("18446744073709551615");
	BigInt a3("18446744073709551616");
	BigInt a4("17446744073709551616");
	BigInt a5("743686428628622989392");
	BigInt a6("-18446744073709551615");
	BigInt a7("-18446744073709551616");
	ASSERT_TRUE(a1 == a2);
	ASSERT_FALSE(a1 == a3);
	ASSERT_FALSE(a1 == a4);
	ASSERT_FALSE(a1 == a5);
	ASSERT_FALSE(a1 == a6);
	ASSERT_TRUE(a6 == a6);
	
	ASSERT_FALSE(a1 != a2);
	ASSERT_TRUE(a1 != a3);
	ASSERT_TRUE(a1 != a4);
	ASSERT_TRUE(a1 != a5);
	ASSERT_TRUE(a1 != a6);
	
	ASSERT_FALSE(a1 > a2);
	ASSERT_FALSE(a1 > a3);
	ASSERT_TRUE(a1 > a4);
	ASSERT_FALSE(a1 > a5);
	ASSERT_TRUE(a1 > a6);
	ASSERT_TRUE(a6 > a7);
	
	ASSERT_TRUE(a1 >= a2);
	ASSERT_FALSE(a1 >= a3);
	ASSERT_TRUE(a1 >= a4);
	ASSERT_FALSE(a1 >= a5);
	ASSERT_TRUE(a1 >= a6);
	ASSERT_TRUE(a6 >= a7);
	
	ASSERT_FALSE(a1 < a2);
	ASSERT_TRUE(a1 < a3);
	ASSERT_FALSE(a1 < a4);
	ASSERT_TRUE(a1 < a5);
	ASSERT_FALSE(a1 < a6);
	ASSERT_FALSE(a6 < a7);
	
	ASSERT_TRUE(a1 <= a2);
	ASSERT_TRUE(a1 <= a3);
	ASSERT_FALSE(a1 <= a4);
	ASSERT_TRUE(a1 <= a5);
	ASSERT_FALSE(a1 <= a6);
	ASSERT_FALSE(a6 <= a7);
}

TEST_F(MyTest, test_add_sub_un_minus)
{
	BigInt a1("18");
	std::string s("7");
	BigInt a2(s);
	ASSERT_STREQ((a1+a2).get_num().c_str(), "25");
	
	BigInt a3("18446744073709551615");
	BigInt a4("743686428628622989392");
	BigInt a5("-18446744073709551615");
	BigInt a6("-743686428628622989392");
	
	ASSERT_STREQ((a3+a4).get_num().c_str(), "762133172702332541007");
	ASSERT_STREQ((a4+a3).get_num().c_str(), "762133172702332541007");
	ASSERT_STREQ((a3+a6).get_num().c_str(), "-725239684554913437777");
	ASSERT_STREQ((a6+a3).get_num().c_str(), "-725239684554913437777");
	ASSERT_STREQ((a5+a4).get_num().c_str(), "725239684554913437777");
	ASSERT_STREQ((a4+a5).get_num().c_str(), "725239684554913437777");
	ASSERT_STREQ((a5+a6).get_num().c_str(), "-762133172702332541007");
	ASSERT_STREQ((a6+a5).get_num().c_str(), "-762133172702332541007");
	
	ASSERT_STREQ((a3-a4).get_num().c_str(), "-725239684554913437777");
	ASSERT_STREQ((a4-a3).get_num().c_str(), "725239684554913437777");
	ASSERT_STREQ((a3-a6).get_num().c_str(), "762133172702332541007");
	ASSERT_STREQ((a6-a3).get_num().c_str(), "-762133172702332541007");
	ASSERT_STREQ((a5-a4).get_num().c_str(), "-762133172702332541007");
	ASSERT_STREQ((a4-a5).get_num().c_str(), "762133172702332541007");
	ASSERT_STREQ((a5-a6).get_num().c_str(), "725239684554913437777");
	ASSERT_STREQ((a6-a5).get_num().c_str(), "-725239684554913437777");
	
	ASSERT_STREQ((-a3).get_num().c_str(), a5.get_num().c_str());
	ASSERT_STREQ((-a4).get_num().c_str(), a6.get_num().c_str());
	ASSERT_STREQ((-(-a3)).get_num().c_str(), a3.get_num().c_str());
	ASSERT_STREQ((a6+a4).get_num().c_str(), "0");
	ASSERT_STREQ((a4-a4).get_num().c_str(), "0");
	
	BigInt a7("10000000000000000000000000000000000");
	ASSERT_STREQ((a7-1).get_num().c_str(), "9999999999999999999999999999999999");
	ASSERT_STREQ((a7+1).get_num().c_str(), "10000000000000000000000000000000001");
}

TEST_F(MyTest, test_mul)
{
	BigInt a1("18");
	std::string s("7");
	BigInt a2(s);
	ASSERT_STREQ((a1*a2).get_num().c_str(), "126");

	BigInt a3("18446744073709551615");
	BigInt a4("743686428628622989392");
	
	ASSERT_STREQ((a3*a4).get_num().c_str(), "13718593220003272554205439550965221468080");
	ASSERT_STREQ((-a3 * (-a4)).get_num().c_str(), "13718593220003272554205439550965221468080");
	ASSERT_STREQ((a3 * (-a4)).get_num().c_str(), "-13718593220003272554205439550965221468080");
	ASSERT_STREQ((-a3 * a4).get_num().c_str(), "-13718593220003272554205439550965221468080");
	
	ASSERT_STREQ((a3 * 1).get_num().c_str(), a3 .get_num().c_str());
	ASSERT_STREQ((a4 * 0).get_num().c_str(), "0");
}

TEST_F(MyTest, test_interesting_case_and_zero)
{
	BigInt a1("9999999999999999999");
	BigInt a2("10000000000000000000");
	BigInt a3("1111111111111111111");
	BigInt a4("5");
	BigInt a5("-5");
	BigInt a6("6");
	
	ASSERT_STREQ((a1 + 1).get_num().c_str(), "10000000000000000000");
	ASSERT_STREQ((a2 - 1).get_num().c_str(), "9999999999999999999");
	ASSERT_STREQ((a2 - a1).get_num().c_str(), "1");
	ASSERT_STREQ((a1 - a2).get_num().c_str(), "-1");
	
	ASSERT_STREQ((a3 * 3).get_num().c_str(), "3333333333333333333");
	ASSERT_STREQ((a3 - 3).get_num().c_str(), "1111111111111111108");
	ASSERT_STREQ((a3 + 3).get_num().c_str(), "1111111111111111114");
	
	ASSERT_STREQ((a1 * 1).get_num().c_str(), "9999999999999999999");
	
	ASSERT_STREQ((a4 * 4).get_num().c_str(), "20");
	ASSERT_STREQ((a4 - 4).get_num().c_str(), "1");
	ASSERT_STREQ((a4 + 4).get_num().c_str(), "9");
	
	ASSERT_STREQ((a4 * 0).get_num().c_str(), "0");
	ASSERT_STREQ((a4 + 0).get_num().c_str(), "5");
	ASSERT_STREQ((a4 - 0).get_num().c_str(), "5");
	
	ASSERT_STREQ((a5 * 0).get_num().c_str(), "0");
	ASSERT_STREQ((a5 + 0).get_num().c_str(), "-5");
	ASSERT_STREQ((a5 - 0).get_num().c_str(), "-5");
	
	ASSERT_STREQ((a4 * a5).get_num().c_str(), "-25");
	ASSERT_STREQ((a4 + a5).get_num().c_str(), "0");
	ASSERT_STREQ((a4 - a5).get_num().c_str(), "10");
	
	ASSERT_STREQ((a5 * a4).get_num().c_str(), "-25");
	ASSERT_STREQ((a5 + a4).get_num().c_str(), "0");
	ASSERT_STREQ((a5 - a4).get_num().c_str(), "-10");
}
int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
