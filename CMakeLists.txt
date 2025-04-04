cmake_minimum_required(VERSION 3.27)
project(Practise CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(CMAKE_BUILD_TYPE Release)

message(STATUS "[ CURRENT BUILD TYPE ] : ${CMAKE_BUILD_TYPE}")

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
# ----------------------------------------------------------------


find_package(pxr REQUIRED CONFIG PATHS "${USD_ROOT}" NO_DEFAULT_PATH)
find_package(TBB REQUIRED)

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
    TBB::tbb
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