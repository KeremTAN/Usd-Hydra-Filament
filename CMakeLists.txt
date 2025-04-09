cmake_minimum_required(VERSION 3.27)

set(CMAKE_C_COMPILER "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


project(HdTutorial)


set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ----------------------- SET FILE PATH ---------------------------
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(USD_ROOT "third_party/usd/debug")
    set(FILAMENT_ROOT "third_party/filament/debug/filament")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(USD_ROOT "third_party/usd/release")
    set(FILAMENT_ROOT "third_party/filament/release/filament")
endif()


file(GLOB sources "src/*.cpp")
file(GLOB headers "include/*.h")
file(GLOB FILAMENT_LIBS "${FILAMENT_ROOT}/lib/universal/*.a")
# -----------------------------------------------------------------


find_package(pxr REQUIRED CONFIG PATHS "${USD_ROOT}")
find_package(Python3 REQUIRED)


file(GLOB headers "${CMAKE_SOURCE_DIR}/headers/*.h")
file(GLOB sources "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_library(HdTutorial SHARED
    ${headers}
    ${sources}
)

target_include_directories(HdTutorial PUBLIC ${USD_ROOT}/include ${headers} ${Python_INCLUDE_DIRS})
target_link_libraries(HdTutorial
PUBLIC
${Python_LIBRARIES}
usd
usdGeom
sdf
pcp
usdHydra
usdImaging
TBB::tbb
"-framework Metal"
"-framework Cocoa"
"-framework CoreVideo" 
)

# Configure runtime search paths (rpath) for dependent libraries.
set_target_properties(HdTutorial PROPERTIES INSTALL_RPATH "@loader_path/${USD_ROOT}/lib")

if(TARGET usdHydra)
   message(STATUS "[ √ ] usdHydra target founded")
else()
   message(WARNING "[ X ] usdHydra target NOT founded\n[ CHECK ] pxrConfig.cmake/pxrTargets.cmake dosyasında sorun olabilir.")
endif()