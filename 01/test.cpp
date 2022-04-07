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


TEST_F(MyTest, test_alloc_0)
{
    Allocator obj;
    obj.makeAllocator(0);
    ASSERT_EQ(obj.alloc(5), nullptr);
    obj.makeAllocator(5);
    ASSERT_EQ(obj.alloc(0), nullptr);
}
TEST_F(MyTest, alloc_before_make)
{
    Allocator obj;
    ASSERT_EQ(obj.alloc(5), nullptr);
}
TEST_F(MyTest, few_make)
{
    Allocator obj;
    obj.makeAllocator(15);
    obj.makeAllocator(10);
    obj.makeAllocator(5);
    ASSERT_EQ(obj.alloc(11), nullptr);
    ASSERT_EQ(obj.alloc(6), nullptr);
    ASSERT_NE(obj.alloc(5), nullptr);
}
TEST_F(MyTest, edge)
{
    Allocator obj;
    obj.makeAllocator(1);
    ASSERT_NE(obj.alloc(1), nullptr);
    ASSERT_EQ(obj.alloc(1), nullptr);
}
TEST_F(MyTest, seq)
{
    Allocator obj;
    obj.makeAllocator(50);
    obj.alloc(20);
    obj.alloc(30);
    ASSERT_EQ(obj.alloc(1), nullptr);
    obj.reset();
    ASSERT_NE(obj.alloc(50), nullptr);
}
TEST_F(MyTest, pointer)
{
    Allocator obj;
    obj.makeAllocator(30);
    char* p1 = obj.alloc(10);
    char* p2 = obj.alloc(10);
    ASSERT_EQ(p2 - p1, 10);
    char* p3 = obj.alloc(10);
    ASSERT_EQ(p3 - p1, 20);
}
int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

