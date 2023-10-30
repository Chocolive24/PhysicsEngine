cmake_minimum_required(VERSION 3.22)
project(PhysicsEngineCommon)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(GTest CONFIG REQUIRED)

# Create the Math library
file(GLOB_RECURSE MATH_SRC_FILES libs/math/include/*.h libs/math/src/*.cpp)
add_library(Math ${MATH_SRC_FILES})
set_target_properties(Math PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(Math PUBLIC libs/math/include/)

# Create the Common library with Math as a dependency
file(GLOB_RECURSE COMMON_SRC_FILES common/include/*.h common/src/*.cpp)
add_library(Common ${COMMON_SRC_FILES})
set_target_properties(Common PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(Common PUBLIC common/include/)
target_link_libraries(Common PUBLIC Math)

# Create the PhysicsEngineCommon library with Math as a dependency
file(GLOB_RECURSE PHYSICS_SRC_FILES physics_engine/include/*.h physics_engine/src/*.cpp)
add_library(PhysicsEngineCommon ${PHYSICS_SRC_FILES})
set_target_properties(PhysicsEngineCommon PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(PhysicsEngineCommon PUBLIC physics_engine/include/)
target_link_libraries(PhysicsEngineCommon PUBLIC Math)

# Create the SDL_AppCommon library with Math as a dependency
file(GLOB_RECURSE SDL_APP_SRC_FILES sdl_application/include/*.h sdl_application/src/*.cpp)
add_library(SDL_AppCommon ${SDL_APP_SRC_FILES})
set_target_properties(SDL_AppCommon PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(SDL_AppCommon PUBLIC sdl_application/include/)
target_link_libraries(SDL_AppCommon PUBLIC SDL2::SDL2 Math Common)

# Create the Samples library with dependencies on PhysicsEngineCommon, SDL_AppCommon, Common, and Math
file(GLOB_RECURSE SAMPLES_SRC_FILES samples/include/*.h samples/src/*.cpp)
add_library(Samples ${SAMPLES_SRC_FILES})
set_target_properties(Samples PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(Samples PUBLIC samples/include/)
target_link_libraries(Samples PUBLIC PhysicsEngineCommon SDL_AppCommon Common Math)

# Create the PhysicsEngine executable with the Samples library as a dependency
add_executable(PhysicsEngine main.cpp)
target_link_libraries(PhysicsEngine PRIVATE Samples)

# Disable SDL main
add_definitions(-DSDL_MAIN_HANDLED)

# Tests Physics Engine
file(GLOB_RECURSE PHYSICS_TEST_FILES physics_engine/tests/*.cpp)
foreach(test_file ${PHYSICS_TEST_FILES} )
    get_filename_component(test_name ${test_file} NAME_WE)

    add_executable(${test_name} ${test_file})

    target_link_libraries(${test_name} PRIVATE PhysicsEngineCommon)
    target_link_libraries(${test_name} PRIVATE GTest::gtest GTest::gtest_main)

    IF(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:AVX2 /Oi /Oy-")
    else()
        set_target_properties(${test_name} PROPERTIES COMPILE_FLAGS "-save-temps -march=haswell -ffast-math -fno-omit-frame-pointer")
    ENDIF()

    set_target_properties (${test_name} PROPERTIES FOLDER Courses)
endforeach()


# Tests Common
file(GLOB_RECURSE COMMON_TEST_FILES common/tests/*.cpp)
foreach(test_file ${COMMON_TEST_FILES} )
    get_filename_component(test_name ${test_file} NAME_WE)

    add_executable(${test_name} ${test_file})

    target_link_libraries(${test_name} PRIVATE Common)
    target_link_libraries(${test_name} PRIVATE GTest::gtest GTest::gtest_main)

    IF(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:AVX2 /Oi /Oy-")
    else()
        set_target_properties(${test_name} PROPERTIES COMPILE_FLAGS "-save-temps -march=haswell -ffast-math -fno-omit-frame-pointer")
    ENDIF()

    set_target_properties (${test_name} PROPERTIES FOLDER Courses)
endforeach()