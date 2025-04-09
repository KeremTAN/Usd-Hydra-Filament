cmake_minimum_required(VERSION 3.27)

set(CMAKE_C_COMPILER "/opt/homebrew/opt/llvm@19/bin/clang")
set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm@19/bin/clang++")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Practise CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)


# ----------------------- SET FILE PATH ---------------------------
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(USD_ROOT "third_party/usd/debug/")
    set(FILAMENT_ROOT "third_party/filament/debug/filament/")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(USD_ROOT "third_party/usd/release/")
    set(FILAMENT_ROOT "third_party/filament/release/filament/")
endif()


file(GLOB sources "src/*.cpp")
file(GLOB headers "include/*.h")
file(GLOB FILAMENT_LIBS "${FILAMENT_ROOT}/lib/universal/*.a")
# -----------------------------------------------------------------

message(STATUS "[ CURRENT BUILD TYPE ] : ${CMAKE_BUILD_TYPE}")
message(STATUS "[ COMPILER ID        ] : ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "[ COMPILER VERSION   ] : ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "[ CXX STANDARD       ] : ${CMAKE_CXX_STANDARD}")


find_package(pxr REQUIRED CONFIG PATHS "${USD_ROOT}")

add_executable(my_program ${sources})

target_link_libraries(my_program
    PRIVATE
    usd
    usdGeom
    sdf
    pcp
    usdHydra
    usdImaging
    ${FILAMENT_LIBS}
    "-framework Metal"
    "-framework Cocoa"
    "-framework CoreVideo" 
)

target_include_directories(my_program PRIVATE
    ${USD_ROOT}/include
    ${FILAMENT_ROOT}/include
    ${headers}
)


target_compile_definitions(my_program PRIVATE
    FILAMENT_DRIVER_METAL=1
)