//
// Created by Olivier on 10.10.2023.
//
#include "dumb.h"

#include <iostream>

Dumb::Dumb(int x)
{
    _x = x;
}

void Dumb::PrintX()
{
    std::cout << _x << "\n";
}

