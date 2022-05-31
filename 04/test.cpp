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
	BigInt a(123);
	std::cout << a << std::endl;
	BigInt a1("18446744073709551615");
	std::cout << a1 << std::endl;
	std::string s("743686428628622989392");
	BigInt a2(s);
	std::cout << a2 << std::endl;
	BigInt a3(a1);
	BigInt a4(std::move(a2));
	std::cout << a3 << std::endl;
	std::cout << a4 << std::endl;
	a4 = a4;
	std::cout << a4 << std::endl;
	a3 = a4;
	a3 = std::move(a1);
	std::cout << a1 << std::endl;
	std::cout << a2 << std::endl;
	std::cout << a3 << std::endl;
	std::cout << a4 << std::endl << std::endl;
//negative	
	BigInt b(-123);
	std::cout << b << std::endl;
	BigInt b1("-18446744073709551615");
	std::cout << b1 << std::endl;
	std::string s2("-743686428628622989392");
	BigInt b2(s2);
	std::cout << b2 << std::endl;
	BigInt b3(b1);
	BigInt b4(std::move(b2));
	std::cout << b3 << std::endl;
	std::cout << b4 << std::endl;
	b4 = b4;
	std::cout << b4 << std::endl;
	b3 = b4;
	b3 = std::move(b1);
	std::cout << b1 << std::endl;
	std::cout << b2 << std::endl;
	std::cout << b3 << std::endl;
	std::cout << b4 << std::endl;
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

int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
