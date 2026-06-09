set(CMAKE_SYSTEM_NAME Linux)

set(CMAKE_C_COMPILER "x86_64-linux-musl-gcc")
set(CMAKE_CXX_COMPILER "x86_64-linux-musl-g++")
set(CMAKE_C_FLAGS_RELEASE "-O2 -ffunction-sections -fdata-sections")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -ffunction-sections -fdata-sections")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-static -s -Wl,--gc-sections")
