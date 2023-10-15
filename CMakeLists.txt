cmake_minimum_required(VERSION 3.22)
project(PhysicsEngineCommon)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(GTest CONFIG REQUIRED)

file(GLOB_RECURSE PHYSICS_SRC_FILES PhysicsEngineCommon/include/*.h PhysicsEngineCommon/src/*.cpp)
add_library(PhysicsEngineCommon ${PHYSICS_SRC_FILES})
set_target_properties(PhysicsEngineCommon PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(PhysicsEngineCommon PUBLIC PhysicsEngineCommon/include/)
target_include_directories(PhysicsEngineCommon PUBLIC PhysicsEngineCommon/libs/Math922/include/)

file(GLOB_RECURSE SRC_FILES include/*.h src/*.cpp)
add_library(Common ${SRC_FILES})
set_target_properties(Common PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(Common PUBLIC include/)
target_link_libraries(Common PUBLIC PhysicsEngineCommon)
target_link_libraries(Common PUBLIC SDL2::SDL2)

add_executable(PhysicsEngine main.cpp)
target_link_libraries(PhysicsEngine PRIVATE Common)
target_include_directories(PhysicsEngine PUBLIC samples/include/)

# Disable SDL main
add_definitions(-DSDL_MAIN_HANDLED)

# Tests
SET(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)
file(GLOB TEST_FILES ${TEST_DIR}/*.cpp )

foreach(test_file ${TEST_FILES} )
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(PhysicsEngine${test_name} ${test_file})

    target_link_libraries(PhysicsEngine${test_name} PUBLIC Common)
    target_link_libraries(PhysicsEngine${test_name} PRIVATE GTest::gtest GTest::gtest_main)

    target_include_directories(PhysicsEngine${test_name} PUBLIC include/)

    IF(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:AVX2 /Oi /Oy-")
    else()
        set_target_properties(PhysicsEngine${test_name} PROPERTIES COMPILE_FLAGS "-save-temps -march=haswell -ffast-math -fno-omit-frame-pointer")
    ENDIF()

    set_target_properties (PhysicsEngine${test_name} PROPERTIES FOLDER Courses)
endforeach()