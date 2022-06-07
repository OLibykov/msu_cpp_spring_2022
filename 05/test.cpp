#include <gtest/gtest.h>
#include "Serializer_Deserializer.hpp"

struct Data {
    bool a, b, c;
    uint64_t d, e, f;
    bool g;
    uint64_t h, i;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c, d, e, f, g, h, i);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c, d, e, f, g, h, i);
    }
        
}; 

struct Data1
{
	uint64_t a;
	bool b;
	uint64_t c;
	template <class Serializer>
	Error serialize(Serializer& serializer)
	{
		return serializer(a, b, c);
	}
	template <class Deserializer>
	Error deserialize(Deserializer& deserializer)
	{
		return deserializer(a, b, c);
	}
};

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

TEST_F(MyTest, test_task)
{
	Data1 x { 1, true, 2 };

	std::stringstream stream;

	Serializer serializer(stream);
	serializer.save(x);

	Data1 y { 0, false, 0 };

	Deserializer deserializer(stream);
	const Error err = deserializer.load(y);

	ASSERT_TRUE(err == Error::NoError);
	ASSERT_EQ(x.a, y.a);
	ASSERT_EQ(x.b, y.b);
	ASSERT_EQ(x.c, y.c);
}

TEST_F(MyTest, test_serializer)
{
	Data x { true, false, true,  1, 2, 3, false, 5, 6};

	std::stringstream stream;

	Serializer serializer(stream);
	serializer.save(x);
	
	std::string tmp_str;
	uint64_t tmp_int;
	
	stream >> tmp_str;
	ASSERT_TRUE(tmp_str == "true");
	stream >> tmp_str;
	ASSERT_TRUE(tmp_str == "false");
	stream >> tmp_str;
	ASSERT_TRUE(tmp_str == "true");
	for (size_t i = 1; i < 7; i ++)
	{
		if (i != 4)
		{
			static_cast<std::istream&>(stream) >> tmp_int;
			ASSERT_EQ(tmp_int, i);
		}
		else
		{
			stream >> tmp_str;
			ASSERT_TRUE(tmp_str == "false");
		}
	}
}

TEST_F(MyTest, test_deserializer)
{
	Data y = {true, true, false, 1, 2, 3, false, 0, 9};
	//not enough arguments
    std::stringstream str1("");
    std::stringstream str2("true");
    std::stringstream str3("34 false");

    //negative number
    std::stringstream str4("false true true -100500 322 12345678, true 0 2147483647");
    //too large number
    std::stringstream str5("false true true 1005000000000000000000000000000000 322 12345678, true 0 2147483647");

    //invalid string token
    std::stringstream str6("false true qwerty 100500 322 4 true 0 2147483647");

    //wrong order
    std::stringstream str7("false true 100500 false 322 12345678 true 0 2147483647");

	//uint64_t max
	std::stringstream str8("false true true 101 14 18446744073709551615 true 230 19");
	
	//uint64_t max + 1
	std::stringstream str9("false true true 101 14 18446744073709551616 true 230 19");
    //all OK
    std::stringstream str10("false true true 101 14 28 true 230 19");
	


	Deserializer deser1(str1);   
    Deserializer deser2(str2);   
    Deserializer deser3(str3);   
    Deserializer deser4(str4);  
    Deserializer deser5(str5); 
    Deserializer deser6(str6);   
    Deserializer deser7(str7);   
    Deserializer deser8(str8); 
	Deserializer deser9(str9); 
	Deserializer deser10(str10); 
	
	ASSERT_TRUE(deser1.load(y) == Error::CorruptedArchive);
    ASSERT_TRUE(deser2.load(y) == Error::CorruptedArchive);
    ASSERT_TRUE(deser3.load(y) == Error::CorruptedArchive);
    ASSERT_TRUE(deser4.load(y) == Error::CorruptedArchive);
    ASSERT_TRUE(deser5.load(y) == Error::CorruptedArchive);
    ASSERT_TRUE(deser6.load(y) == Error::CorruptedArchive);
    ASSERT_TRUE(deser7.load(y) == Error::CorruptedArchive);
    ASSERT_TRUE(deser8.load(y) == Error::NoError);
	ASSERT_TRUE(deser9.load(y) == Error::CorruptedArchive);
    ASSERT_TRUE(deser10.load(y) == Error::NoError);
	
	ASSERT_FALSE(y.a);
    ASSERT_TRUE(y.b);
    ASSERT_TRUE(y.c);
    ASSERT_EQ(y.d, 101);
    ASSERT_EQ(y.e, 14);
    ASSERT_EQ(y.f, 28);
    ASSERT_TRUE(y.e);
    ASSERT_EQ(y.h, 230);
    ASSERT_EQ(y.i, 19);
}	
int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}