#include <gtest/gtest.h>
#include "My_Parser.hpp"

void (*start_1)() = [](){std::cout << "Start Parsing lambda" << std::endl;};
void(*end_1)(std::vector<uint64_t>, std::vector<uint64_t>) = [](std::vector<uint64_t> , std::vector<uint64_t>){std::cout << "End Parsing lambda" << std::endl;};
uint64_t (*num_1)(uint64_t) = [](uint64_t val){return val;};
uint64_t (*str_1)(const std::string) = [](const std::string str){return str.length();};

void start_2(){std::cout << "Start Parsing common" << std::endl;}
void end_2(std::vector<uint64_t> num, std::vector<uint64_t> str){
	for (auto it = num.begin(); it != num.end(); it++){std::cout << *it << ' ';}
	std::cout << std::endl;
	for (auto it = str.begin(); it != str.end(); it++){std::cout << *it << ' ';}
	std::cout << std::endl;	
	std::cout << "End Parsing common" << std::endl;
}
uint64_t num_2(uint64_t value){
	return 2 * value;
}
uint64_t count_vowel_letter(const std::string str){
    uint64_t cnt = 0;
    const std::string arr_lett = "AaEeIiOoUuYy";
    for(size_t i = 0; i < str.length(); i++){
        for(size_t j = 0; j < arr_lett.length(); j++){
            arr_lett[j] == str[i]? cnt++ : 0;
		}
    }
    return cnt;
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
	obj.Parse("Hello 222 world 1234 432");
	ASSERT_EQ(obj.get_last_num(),  432);
	ASSERT_STREQ(obj.get_last_str().c_str(),  "world");
}

TEST_F(MyTest, with_lambda)
{
	TokenParser obj;

	obj.SetStartCallback(start_1);
	obj.SetEndCallback(end_1);
	obj.SetDigitTokenCallback(num_1);
	obj.SetStringTokenCallback(str_1);
	
	obj.Parse("hello 222 worlddd 1234 0");
	
	ASSERT_EQ(obj.get_last_num(),  0);
	auto stat_str = obj.get_stat_str();
	auto stat_num = obj.get_stat_num();
	ASSERT_EQ(stat_str.empty(), false);
	ASSERT_EQ(stat_num.empty(), false);
	std::vector<uint64_t> test_num = {222, 1234, 0};
	std::vector<uint64_t> test_str = {5, 7};
	for (size_t i = 0; i < test_num.size(); i++){ASSERT_EQ(test_num[i], stat_num[i]);}
	for (size_t i = 0; i < test_str.size(); i++){ASSERT_EQ(test_str[i], stat_str[i]);}
}
TEST_F(MyTest, with_common_function)
{
	TokenParser obj;

	obj.SetStartCallback(start_2);
	obj.SetEndCallback(end_2);
	obj.SetDigitTokenCallback(num_2);
	obj.SetStringTokenCallback(count_vowel_letter);
	
	obj.Parse("hello 222 worlddd 1234 0");
	auto stat_str = obj.get_stat_str();
	auto stat_num = obj.get_stat_num();
	ASSERT_EQ(obj.get_last_num(),  0);
	ASSERT_EQ(stat_str.empty(), false);
	ASSERT_EQ(stat_num.empty(), false);

	std::vector<uint64_t> test_num = {444, 2468, 0};
	std::vector<uint64_t> test_str = {2, 1};
	for (size_t i = 0; i < test_num.size(); i++){ASSERT_EQ(test_num[i], stat_num[i]);}
	for (size_t i = 0; i < test_str.size(); i++){ASSERT_EQ(test_str[i], stat_str[i]);}
}
TEST_F(MyTest, sequence_parse)
{
	TokenParser obj;

	obj.SetStartCallback(start_2);
	obj.SetEndCallback(end_2);
	obj.SetDigitTokenCallback(num_1);
	
	obj.Parse("222 0001234 0");
	auto stat_num = obj.get_stat_num();
	auto stat_str = obj.get_stat_str();
	ASSERT_EQ(stat_str.empty(), true);
	ASSERT_EQ(stat_num.empty(), false);
	std::vector<uint64_t> test_num = {222, 1234, 0};
	for (size_t i = 0; i < test_num.size(); i++){ASSERT_EQ(test_num[i], stat_num[i]);}
	
	obj.SetDigitTokenCallback(num_2);
	obj.SetStringTokenCallback(count_vowel_letter);	
	
	obj.Parse("4Hello world4	Postavte tr0e4ku	3pozaluista3");
	
	stat_num = obj.get_stat_num();
	stat_str = obj.get_stat_str();
	ASSERT_EQ(stat_str.empty(), false);
	ASSERT_EQ(stat_num.empty(), false);
	std::vector<uint64_t> test_str = {2, 1, 3, 2, 5};
	for (size_t i = 0; i < test_num.size(); i++){ASSERT_EQ(test_num[i], stat_num[i]);}
	for (size_t i = 0; i < test_str.size(); i++){ASSERT_EQ(test_str[i], stat_str[i]);}
	
	obj.SetStringTokenCallback(str_1);
	obj.Parse("1	2 tree 4 5 vishel zaichik	walk");
	
	stat_num = obj.get_stat_num();
	stat_str = obj.get_stat_str();
	ASSERT_EQ(stat_str.empty(), false);
	ASSERT_EQ(stat_num.empty(), false);
	std::vector<uint64_t> test_str2 = {2, 1, 3, 2, 5, 4, 6, 7, 4};
	std::vector<uint64_t> test_num2 = {222, 1234, 0,  2, 4, 8, 10};
	for (size_t i = 0; i < test_num2.size(); i++){ASSERT_EQ(test_num2[i], stat_num[i]);}
	for (size_t i = 0; i < test_str2.size(); i++){ASSERT_EQ(test_str2[i], stat_str[i]);}
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

