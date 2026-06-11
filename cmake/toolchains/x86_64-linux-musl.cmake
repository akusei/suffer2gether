set(CMAKE_SYSTEM_NAME Linux)

set(CMAKE_C_COMPILER "zig" "cc")
set(CMAKE_CXX_COMPILER "zig" "c++")
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

set(CMAKE_C_FLAGS_RELEASE "-target x86_64-linux-musl -O2 -ffunction-sections -fdata-sections")
set(CMAKE_CXX_FLAGS_RELEASE "-target x86_64-linux-musl -O2 -ffunction-sections -fdata-sections")

set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-static -s -Wl,--gc-sections")
