cmake_minimum_required(VERSION 3.27)

# set(CMAKE_C_COMPILER "/opt/homebrew/opt/llvm@19/bin/clang")
# set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm@19/bin/clang++")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(HdTutorial)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(pxr REQUIRED COMPONENTS hd)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(FILAMENT_ROOT "third_party/filament/debug/filament/")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(FILAMENT_ROOT "third_party/filament/release/filament/")
endif()

file(GLOB FILAMENT_LIBS "${FILAMENT_ROOT}/lib/universal/*.a" "${FILAMENT_ROOT}/lib/universal/*.dylib")

file(GLOB headers "${CMAKE_SOURCE_DIR}/headers/*.h")
file(GLOB sources "${CMAKE_SOURCE_DIR}/src/*.cpp")


add_library(HdTutorial SHARED
    ${headers}
    ${sources}
)

target_include_directories(HdTutorial PUBLIC
${USD_INCLUDE_DIRS}
${headers}
${FILAMENT_ROOT}/include
)

target_link_libraries(HdTutorial PRIVATE
hd
${FILAMENT_LIBS}
"-framework Metal"
"-framework Cocoa"
"-framework CoreVideo" 
)


set_target_properties(HdTutorial PROPERTIES INSTALL_RPATH "@loader_path")

if(UNIX)
  target_compile_options(HdTutorial PRIVATE -fPIC)
  set_target_properties(HdTutorial PROPERTIES PREFIX "")
endif()