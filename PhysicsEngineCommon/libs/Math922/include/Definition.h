#pragma once
//
// Created by Coch on 07.10.2023.
//

#ifdef MSVC
#define NOALIAS __declspec(noalias)
#else
#define NOALIAS __attribute__((const))
#endif