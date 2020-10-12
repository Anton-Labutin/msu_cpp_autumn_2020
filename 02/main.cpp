//
//  main.cpp
//  My Allocator
/*
 Что должно происходить:
 1) При вызове makeAllocator аллоцируется динамическая память указанного
    размера (при помощи new);
 2) При вызове alloc возвращает указатель на блок запрошенного размера
    или nullptr, если места недостаточно;
 3) Пользователь может вызвать метод alloc несколько раз подряд.
    Соответственно нужно хранить не только указатель на начало памяти,
    но и смещение от начала (offset) --- то место, где располагается ещё
    не занятая пользователем память;
 4) После вызова reset аллокатор позволяет использовать свою память снова.
    То есть память, ранее выделенная при помощи alloc, становится
    "невалидной", её пользователь может переиспользовать, вызвав опять alloc.
    offset при методе reset снова указывает на начало;
 5) delete вызывается только в деструкторе (но никак не при reset)!
 6) При вызове makeAllocator аллоцируется указанный размер, после чего
    при вызове alloc возвращает указатель на блок запрошенного размера
    или nullptr, если места недостаточно. После вызова reset аллокатор
    позволяет использовать свою память снова.
 */
//
//  Created by Лабутин Антон Александрович on 10.10.2020.
//

#include <iostream>

#include "Allocator/my_allocator.hpp"
#include "Tests/tests.hpp"

int
main()
{
    TestAllocator();
    
    return 0;
}