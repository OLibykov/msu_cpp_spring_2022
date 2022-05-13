#include <gtest/gtest.h>
#include "My_Parser.hpp"

std::vector<uint64_t> test_vec_num;
std::vector<std::string> test_vec_str;

void (*start_1)() = [](){test_vec_num.push_back(0);};
void(*end_1)() = [](){test_vec_num.push_back(0);};
void (*num_1)(uint64_t) = [](uint64_t val) {test_vec_num.push_back(val);};
void (*str_1)(const std::string) = [](const std::string str) {test_vec_str.push_back(str);};

void start_2(){test_vec_str.push_back("Start");}
void end_2(){test_vec_str.push_back("End");}
void start_3(){}
void end_3(){}
void num_2(uint64_t value){test_vec_num.push_back(value - 1);}
void str_2(const std::string str){
	test_vec_str.push_back(str + "a");
}
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

TEST_F(MyTest, test_without_setup_callback)
{
    TokenParser obj;
	test_vec_num.clear();
	test_vec_str.clear();
	obj.Parse("Hello 222 world 1234 432");
	ASSERT_TRUE(test_vec_num.empty());
	ASSERT_TRUE(test_vec_str.empty());
}

TEST_F(MyTest, test_setup_callback_nullptr)
{
    TokenParser obj;
	obj.SetStartCallback(nullptr);
	obj.SetEndCallback(nullptr);
	obj.SetDigitTokenCallback(nullptr);
	obj.SetStringTokenCallback(nullptr);
	test_vec_num.clear();
	test_vec_str.clear();
	obj.Parse("Hello 222 world 1234 432");
	ASSERT_TRUE(test_vec_num.empty());
	ASSERT_TRUE(test_vec_str.empty());
}

TEST_F(MyTest, with_lambda)
{
	TokenParser obj;

	obj.SetStartCallback(start_1);
	obj.SetEndCallback(end_1);
	obj.SetDigitTokenCallback(num_1);
	obj.SetStringTokenCallback(str_1);
	
	test_vec_num.clear();
	test_vec_str.clear();
	obj.Parse("hello 222 worlddd 1234 1");
	
	ASSERT_FALSE(test_vec_num.empty());
	ASSERT_FALSE(test_vec_str.empty());
	std::vector<uint64_t> right_num = {0, 222, 1234, 1, 0};
	std::vector<std::string> right_str = {"hello", "worlddd"};
	ASSERT_EQ(test_vec_num.size(), right_num.size());
	ASSERT_EQ(test_vec_str.size(), right_str.size());

	for (size_t i = 0; i < right_num.size(); i++){ASSERT_EQ(test_vec_num[i], right_num[i]);}
	for (size_t i = 0; i < right_str.size(); i++){ASSERT_STREQ(test_vec_str[i].c_str(), right_str[i].c_str());}
}
TEST_F(MyTest, with_common_function)
{
	TokenParser obj;

	obj.SetStartCallback(start_2);
	obj.SetEndCallback(end_2);
	obj.SetDigitTokenCallback(num_2);
	obj.SetStringTokenCallback(str_2);
	
	test_vec_num.clear();
	test_vec_str.clear();
	
	obj.Parse("hello 222 worlddd 1234 5");
	
	ASSERT_FALSE(test_vec_num.empty());
	ASSERT_FALSE(test_vec_str.empty());

	std::vector<uint64_t> right_num = {221, 1233, 4};
	std::vector<std::string> right_str = {"Start", "helloa", "worlddda", "End"};
	
	ASSERT_EQ(test_vec_num.size(), right_num.size());
	ASSERT_EQ(test_vec_str.size(), right_str.size());

	for (size_t i = 0; i < right_num.size(); i++){ASSERT_EQ(test_vec_num[i], right_num[i]);}
	for (size_t i = 0; i < right_str.size(); i++){ASSERT_STREQ(test_vec_str[i].c_str(), right_str[i].c_str());}
}
TEST_F(MyTest, sequence_parse)
{
	TokenParser obj;

	obj.SetStartCallback(start_1);
	obj.SetEndCallback(end_1);
	obj.SetDigitTokenCallback(num_1);
	
	test_vec_num.clear();
	test_vec_str.clear();
	
	obj.Parse("222 0001234 15");

	ASSERT_FALSE(test_vec_num.empty());
	ASSERT_TRUE(test_vec_str.empty());
	
	std::vector<uint64_t> right_num = {0, 222, 1234, 15, 0};
	ASSERT_EQ(test_vec_num.size(), right_num.size());
	for (size_t i = 0; i < test_vec_num.size(); i++){ASSERT_EQ(test_vec_num[i], right_num[i]);}
	
	obj.SetStartCallback(start_2);
	obj.SetEndCallback(end_2);
	obj.SetDigitTokenCallback(num_2);
	obj.SetStringTokenCallback(str_2);	
	
	obj.Parse("Hello world42	Postavte tr0e4ku	33pozaluista33");
	
	ASSERT_FALSE(test_vec_str.empty());
	ASSERT_FALSE(test_vec_num.empty());
	std::vector<std::string> right_str = {"Start", "Helloa", "world42a", "Postavtea", "tr0e4kua", "33pozaluista33a", "End"};
	ASSERT_EQ(test_vec_num.size(), right_num.size());
	ASSERT_EQ(test_vec_str.size(), right_str.size());
	
	for (size_t i = 0; i < test_vec_num.size(); i++){ASSERT_EQ(test_vec_num[i], right_num[i]);}
	for (size_t i = 0; i < test_vec_str.size(); i++){ASSERT_STREQ(test_vec_str[i].c_str(), right_str[i].c_str());}
	
	obj.SetStringTokenCallback(str_1);
	obj.Parse("1	2 tree 4 5 vishel zaichik	walk");
	
	ASSERT_FALSE(test_vec_str.empty());
	ASSERT_FALSE(test_vec_num.empty());
	
	std::vector<std::string> right_str2 = {"Start","Helloa", "world42a", "Postavtea", "tr0e4kua", "33pozaluista33a", "End", "Start", "tree", "vishel", "zaichik", "walk", "End"};
	std::vector<uint64_t> right_num2 = {0, 222, 1234, 15, 0,  0, 1, 3, 4};
	
	ASSERT_EQ(test_vec_num.size(), right_num2.size());
	ASSERT_EQ(test_vec_str.size(), right_str2.size());
	
	for (size_t i = 0; i < test_vec_num.size(); i++){ASSERT_EQ(test_vec_num[i], right_num2[i]);}
	for (size_t i = 0; i < test_vec_str.size(); i++){ASSERT_STREQ(test_vec_str[i].c_str(), right_str2[i].c_str());}
}
TEST_F(MyTest, edge_condition)
{
	TokenParser obj;

	obj.SetStartCallback(start_3);
	obj.SetEndCallback(end_3);
	obj.SetDigitTokenCallback(num_1);
	obj.SetStringTokenCallback(str_1);
	
	test_vec_num.clear();
	test_vec_str.clear();
	
	obj.Parse("");
	
	ASSERT_TRUE(test_vec_num.empty());
	ASSERT_TRUE(test_vec_str.empty());
	
	test_vec_num.clear();
	test_vec_str.clear();
	
	obj.Parse(" 		  ");
	
	ASSERT_TRUE(test_vec_num.empty());
	ASSERT_TRUE(test_vec_str.empty());
	
	obj.Parse("    1    ");
	
	ASSERT_FALSE(test_vec_num.empty());
	ASSERT_TRUE(test_vec_str.empty());
	ASSERT_EQ(test_vec_num[0], 1);
	
	obj.Parse("    a    ");
	
	ASSERT_FALSE(test_vec_num.empty());
	ASSERT_FALSE(test_vec_str.empty());
	ASSERT_EQ(test_vec_num[0], 1);
	ASSERT_STREQ(test_vec_str[0].c_str(), "a");
	ASSERT_EQ(test_vec_num.size(), 1);
	ASSERT_EQ(test_vec_str.size(), 1);
	
	test_vec_num.clear();
	test_vec_str.clear();
	
	obj.Parse("42str");
	ASSERT_TRUE(test_vec_num.empty());
	ASSERT_FALSE(test_vec_str.empty());
	ASSERT_STREQ(test_vec_str[0].c_str(), "42str");
	ASSERT_EQ(test_vec_str.size(), 1);
	
	test_vec_num.clear();
	test_vec_str.clear();
	
	obj.Parse("0");
	ASSERT_FALSE(test_vec_num.empty());
	ASSERT_TRUE(test_vec_str.empty());
	ASSERT_EQ(test_vec_num[0], 0);
	ASSERT_EQ(test_vec_num.size(), 1);
	
	test_vec_num.clear();
	test_vec_str.clear();
	
	obj.Parse("18446744073709551615");
	ASSERT_FALSE(test_vec_num.empty());
	ASSERT_TRUE(test_vec_str.empty());
	ASSERT_EQ(test_vec_num[0], std::numeric_limits<uint64_t>::max());
	ASSERT_EQ(test_vec_num.size(), 1);
	
	test_vec_num.clear();
	test_vec_str.clear();
	
	obj.Parse("18446744073709551616 1844674407370955161500000000000000000000000000000000");
	ASSERT_TRUE(test_vec_num.empty());
	ASSERT_FALSE(test_vec_str.empty());
	ASSERT_STREQ(test_vec_str[0].c_str(), "18446744073709551616");
	ASSERT_STREQ(test_vec_str[1].c_str(), "1844674407370955161500000000000000000000000000000000");
	ASSERT_EQ(test_vec_str.size(), 2);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

