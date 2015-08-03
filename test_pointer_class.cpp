#include "test_pointer_class.h"
#include <cstdlib>
#include <iostream>

test_pointer_class::test_pointer_class()
{
    cout << "test_ptr_constructor";
}

test_pointer_class::~test_pointer_class()
{
    cout << "test_ptr_destructor";
}
