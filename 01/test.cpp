#include <gtest/gtest.h>
#include "allocator.hpp"

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

TEST_F(MyTest, test_normal_work)
{
    Allocator obj;
    obj.makeAllocator(10);
    ASSERT_NE(obj.alloc(6), nullptr);
    ASSERT_NE(obj.alloc(4), nullptr);
    obj.reset(); 
    ASSERT_NE(obj.alloc(10), nullptr);
    obj.makeAllocator(20);
    ASSERT_NE(obj.alloc(20), nullptr);
}
    
TEST_F(MyTest, test_not_normal_work)
{
    Allocator obj;
    obj.makeAllocator(10);
    ASSERT_EQ(obj.alloc(15), nullptr);
    obj.makeAllocator(20);
    ASSERT_NE(obj.alloc(15), nullptr);
    ASSERT_NE(obj.alloc(3), nullptr);
    ASSERT_EQ(obj.alloc(3), nullptr);
    obj.reset();
    ASSERT_NE(obj.alloc(5), nullptr);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

