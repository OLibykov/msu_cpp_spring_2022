#include <iostream>
#include <fstream>
#include <cassert>
#include "mysort.hpp"

using namespace std;

int main()
{
    size_t TrueCount = 8388608;// на 1 байт больше 8 мб
    ofstream ofile;
    uint64_t t;
    ifstream file;
    // 1 тест, обратный порядок
    ofile.open("binary.dat", ios::binary);
    if (!ofile.is_open())
    {
        cout << "Can not open file\n";
        return 0;
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
            assert(t == i);
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
    // 2 тест, всё отсортированно
    ofile.open("binary.dat", ios::binary);
    if (!ofile.is_open())
    {
        cout << "Can not open file\n";
        return 0;
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
            assert(t == i);
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