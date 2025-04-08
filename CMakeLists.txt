cmake_minimum_required(VERSION 3.27)

# set(CMAKE_C_COMPILER "/opt/homebrew/opt/llvm@19/bin/clang")
# set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm@19/bin/clang++")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(HdTutorial)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(pxr REQUIRED COMPONENTS hd)

file(GLOB headers "${CMAKE_SOURCE_DIR}/headers/*.h")
file(GLOB sources "${CMAKE_SOURCE_DIR}/src/*.cpp")


add_library(HdTutorial SHARED
    ${headers}
    ${sources}
)

target_include_directories(HdTutorial PUBLIC ${USD_INCLUDE_DIRS} ${headers})
target_link_libraries(HdTutorial PRIVATE hd)
set_target_properties(HdTutorial PROPERTIES INSTALL_RPATH "@loader_path")


if(UNIX)
  target_compile_options(HdTutorial PRIVATE -fPIC)
  set_target_properties(HdTutorial PROPERTIES PREFIX "")
endif()