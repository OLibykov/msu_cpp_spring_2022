#include <gtest/gtest.h>
#include <iostream>
#include "Vector.h"

using namespace std;

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

class user_class
{
    int x;    
public:
	user_class() : x(0) {}
    user_class(int xx) : x(xx) {}
	user_class& operator =(user_class&& xx){
		x = xx.get();
		return *this;
	}
	user_class& operator =(const user_class& xx){
		x = xx.get();
		return *this;
	}
    user_class(const user_class &obj) : x(obj.get()) {}
	user_class(user_class &&obj) : x(obj.get()) {}
    int get() const { return x; }
};

TEST_F(MyTest, test_){
    Vector<int> v1;
    Vector<int> v2(5);
    Vector<std::string> vec_str(10, "hello");

    ASSERT_EQ(v1.size(), 0);
	ASSERT_EQ(v1.capacity(), 0);
    ASSERT_EQ(v2.size(), 5);
	ASSERT_EQ(v2.capacity(), 5);
	ASSERT_EQ(vec_str.size(), 10);
	ASSERT_EQ(vec_str.capacity(), 10);

    ASSERT_TRUE(v1.empty());
    ASSERT_FALSE(v2.empty());
	
	ASSERT_NO_THROW(v1.pop_back());
    v2.pop_back();
    ASSERT_EQ(v2.size(), 4);

    vec_str[1] = "world";
    std::cout << vec_str[0] << " " << vec_str[1] << std::endl;
    
    vec_str.reserve(11);
    vec_str.push_back("123");
    vec_str.push_back("456");
    ASSERT_EQ(vec_str.size(), 12);

    int x = 1;
    v1.push_back(x);
    v1.push_back(std::move(x));
    ASSERT_EQ(v1.size(), 2);
    v2.resize(2);
    v2.resize(4);

    v2.resize(7, 7);
    for (int i = 0; i < 7; ++i){
        if (i < 4){
			ASSERT_EQ(v2[i], 0);
		}
		else{
			ASSERT_EQ(v2[i], 7);
		}
	}
    ASSERT_EQ(v2.capacity(), 10); // 7 > 5 => cap *= 2 --> 5 * 2 = 10

    vec_str.reserve(30);
    ASSERT_TRUE(vec_str.capacity() >= 30);
	
	size_t count = 0;
    for (auto it = v2.begin(); it != v2.end(); ++it) {	
		ASSERT_EQ(*it, v2[count]);
		count++;
    }
	
    ASSERT_EQ(*(v2.begin() + 2), 0);
    ASSERT_EQ(*(v2.end() - 2), 7);
	v2[5] = 11;
    auto it1 = v2.end();
    --it1;
    it1--;
    ASSERT_EQ(*it1, 11);
	ASSERT_EQ(*(it1 - 1), 7);
	ASSERT_EQ(*(it1 - 2), 0);

    for (auto it = v2.rbegin(); it != v2.rend(); it++) {
		count--;
		ASSERT_EQ(*it, v2[count]);
    }
 
    ASSERT_THROW(vec_str.reserve(std::numeric_limits<size_t>::max()), std::length_error);   

    vec_str.clear();
    ASSERT_TRUE(vec_str.size() == 0 && vec_str.begin() == vec_str.end());
 // Пользовательский класс
    Vector<user_class> class_v(10, user_class(10));
    ASSERT_EQ(class_v[2].get(), 10);
    class_v.reserve(100);
    ASSERT_TRUE(class_v.size() == 10 && class_v.capacity() >= 100 && class_v[2].get() == 10);
	class_v.push_back(user_class(1));
	class_v.push_back(user_class(2));
    class_v.push_back(user_class(3));
    class_v.push_back(user_class(4));
	
	count = 0;
	for (auto it = class_v.begin(); it != class_v.end(); it++) {
		ASSERT_EQ((*it).get(), class_v[count].get());
		count++;
    }
}