# Type Name Library

## Introduction

Use this library to get the name of a type for logging, error messages etc.
All POD types are supported as well as most data types (classes) provided by the STL. And you can extend the library to cover your own data types too.

## Examples / Usage

Simply include the header file "celma/type_name.hpp" and then use the `type<>` template class:

    #include <iostream>
    #include "celma/type_name.hpp"
    
    int main()
    {
       std::cout << celma::type< std::string>::name() << std::endl;  
    }

If a type is unknown, the string "unknown" is returned, otherwise the name of the type.
