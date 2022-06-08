#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include "mysort.hpp"

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

TEST_F(MyTest, test_reverse){
    size_t TrueCount = 8388608;// на 1 байт больше 8 мб
    ofstream ofile;
    uint64_t t;
    ifstream file;
    // 1 тест, обратный порядок
    ofile.open("binary.dat", ios::binary);
    if (!ofile.is_open())
    {
        cout << "Can not open file\n";
        return;
    }

    for (uint64_t i = TrueCount; i > 0; i--)
        ofile.write((char*)&i, sizeof(uint64_t));
    ofile.close();

    try
    {
        mysort("binary.dat", "out.dat");

        file.open("out.dat", ios::binary);

        for (uint64_t i = 1; i <= TrueCount; ++i)
        {
            file.read((char*)&t, sizeof(uint64_t));
            ASSERT_EQ(t, i);
        }
        file.close();
        cout << "Ok\n";
    }
    catch (const exception& err)
    {
        cout << err.what();
    }
    catch (...)
    {
        cout << "Error\n";
    }
}
TEST_F(MyTest, test_allready_done){
	size_t TrueCount = 8388608;// на 1 байт больше 8 мб
    ofstream ofile;
    uint64_t t;
    ifstream file;
    // 2 тест, всё отсортированно
    ofile.open("binary.dat", ios::binary);
    if (!ofile.is_open())
    {
        cout << "Can not open file\n";
        return;
    }

    for (uint64_t i = 0; i < TrueCount; i++)
        ofile.write((char*)&i, sizeof(uint64_t));
    ofile.close();

    try
    {
        mysort("binary.dat", "out.dat");

        file.open("out.dat", ios::binary);
        for (uint64_t i = 0; i < TrueCount; ++i)
        {
            file.read((char*)&t, sizeof(uint64_t));
            ASSERT_EQ(t, i);
        }
        file.close();
        cout << "Ok\n";
    }
    catch (const exception& err)
    {
        cout << err.what();
    }
    catch (...)
    {
        cout << "Error\n";
    }

    std::remove("binary.dat");
    std::remove("out.dat");
    std::remove("tmp.bin");
}

int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}