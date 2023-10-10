cmake_minimum_required(VERSION 3.22)
project(PhysicsEngine)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(GTest CONFIG REQUIRED)

add_executable(PhysicsEngine main.cpp)

file(GLOB_RECURSE SRC_FILES include/*.h src/*.cpp)
add_library(PhysicsEngineCommon ${SRC_FILES})
set_target_properties(PhysicsEngineCommon PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(PhysicsEngineCommon PUBLIC include/)
target_include_directories(PhysicsEngineCommon PUBLIC libs/Math922/include/)
target_link_libraries(PhysicsEngine PRIVATE PhysicsEngineCommon SDL2::SDL2)

# Disable SDL main
add_definitions(-DSDL_MAIN_HANDLED)

# Lib Math922
add_subdirectory(libs/Math922)

# Tests
SET(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)
file(GLOB TEST_FILES ${TEST_DIR}/*.cpp )

foreach(test_file ${TEST_FILES} )
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(PhysicsEngine${test_name} ${test_file})

    target_link_libraries(PhysicsEngine${test_name} PUBLIC PhysicsEngineCommon)
    target_link_libraries(PhysicsEngine${test_name} PRIVATE GTest::gtest GTest::gtest_main)

    IF(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:AVX2 /Oi /Oy-")
    else()
        set_target_properties(${test_name} PROPERTIES COMPILE_FLAGS "-save-temps -march=haswell -ffast-math -fno-omit-frame-pointer")
    ENDIF()

    set_target_properties (${test_name} PROPERTIES FOLDER Courses)
endforeach()