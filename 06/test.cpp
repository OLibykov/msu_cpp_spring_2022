#include <gtest/gtest.h>
#include "format_str.cpp"


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

TEST_F(MyTest, test_format){
    std::string s1 = format("{1}+{1} = {0}", 4, "two");
	ASSERT_STREQ(s1.c_str(), "two+two = 4");
    std::string pi("PI");
    std::string s2 = format("{1} equals to {0}", 3.14159, pi);
    ASSERT_STREQ(s2.c_str(), "PI equals to 3.14159");
 
    const char *chr = "{0}{4}{3} + {1}{4}{3} = {2}";

    std::string s3 = format(chr, "sin", "cos", 1, "(x)", "^2");
    ASSERT_STREQ(s3.c_str(), "sin^2(x) + cos^2(x) = 1");
}

TEST_F(MyTest, test_without_format){
    std::string text = "Last Christmas, I gave you my heart";
    ASSERT_STREQ(format(text, 1, 2, 3, 4).c_str(), "Last Christmas, I gave you my heart");
}
TEST_F(MyTest, test_exception){
	std::string text = "Last Christmas, I gave you my heart";
    text.push_back('{');
	std::string format1 = "{0}}{1}";
	std::string format2 = "{-2} {0} {2}";
	std::string format3 = "{2} {0} {4}";
	std::string format4 = "{2} {0} {}";
    ASSERT_THROW(format(text, 1, 2, 3, 4), std::runtime_error);
	ASSERT_THROW(format(format1, 1, 2, 3, 4), std::runtime_error);
	ASSERT_THROW(format(format2, 1, 2, 3, 4), std::runtime_error);
	ASSERT_THROW(format(format3, 1, 2, 3, 4), std::runtime_error);
	ASSERT_THROW(format(format4, 1, 2, 3, 4), std::runtime_error);
}

int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
