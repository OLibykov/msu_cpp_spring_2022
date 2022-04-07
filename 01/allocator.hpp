#pragma once
#include <iostream>
class Allocator
{
private:
    size_t max_size = 0;
    size_t offset = 0;
    char* ptr = nullptr;
public:
    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
    ~Allocator();
};
