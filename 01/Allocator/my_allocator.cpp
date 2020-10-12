//
//  my_allocator.cpp
//  My Allocator
//
//  Created by Лабутин Антон Александрович on 10.10.2020.
//

#include "my_allocator.hpp"

char*
Allocator::GetMemory(size_t size)
{
    if (offset + size <= maxSize) {
        offset += size;
        return memory + offset - size;
    } else {
        return nullptr;
    }
}

void
Allocator::MakeAllocator(size_t maxSz)
{
    if (memory) {
        delete [] memory;
    }

    memory = new char [maxSize];
    maxSize = maxSz;
}

char*
Allocator::Alloc(size_t size)
{
    return GetMemory(size);
}

void
Allocator::Reset()
{
    offset = 0;
}

size_t
Allocator::GetMaxSize() const
{
    return maxSize;
}

size_t
Allocator::GetLeftSize() const
{
    return maxSize - offset;
}
