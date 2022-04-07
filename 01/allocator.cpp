#include "allocator.hpp"

void Allocator::makeAllocator(size_t maxSize){
    if (maxSize <= 0){
       return;
    }
    if (ptr != nullptr){delete[] ptr;}
    ptr = new char[maxSize];
    offset = 0;
    max_size = maxSize;
}
char* Allocator::alloc(size_t size){

    if (size <= 0){
        return nullptr;
    }
    if (offset + size > max_size){
        return nullptr;
    }
    else{
        char* tmp = ptr + offset;
        offset += size;
        return tmp;
    }
}
void Allocator::reset(){
    offset = 0;
}
Allocator::~Allocator(){
    delete[] ptr;
    ptr = nullptr;
}
