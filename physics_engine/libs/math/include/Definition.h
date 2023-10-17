#pragma once

/**
 * @author Constantin
 */

#ifdef MSVC
#define NOALIAS __declspec(noalias)
#else
#define NOALIAS __attribute__((const))
#endif