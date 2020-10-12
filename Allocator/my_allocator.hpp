//
//  my_allocator.hpp
//  My Allocator
//
//  Created by Лабутин Антон Александрович on 10.10.2020.
//

#ifndef my_allocator_hpp
#define my_allocator_hpp

#include <cstddef>

class Allocator {
    char *memory = nullptr;
    size_t maxSize = 0;
    size_t offset = 0;

    char*
    GetMemory(size_t);

public:
    Allocator() {}

    void
    MakeAllocator(size_t);

    char*
    Alloc(size_t);

    void
    Reset();

    size_t
    GetMaxSize() const;

    size_t
    GetLeftSize() const;

    ~Allocator()
    {
        if (memory) {
            delete [] memory;
        }
    }
};

#endif /* my_allocator_hpp */
