#pragma once
#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <cstdint>

// Mocking Windows types so CPatcher compiles on Linux without changes
typedef int BOOL;
typedef uint32_t DWORD;
typedef uint8_t BYTE;

#define TRUE 1
#define FALSE 0

#endif
