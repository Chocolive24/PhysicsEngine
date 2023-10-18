cmake_minimum_required(VERSION 3.22)
project(PhysicsEngineCommon)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(GTest CONFIG REQUIRED)

file(GLOB_RECURSE PHYSICS_SRC_FILES physics_engine/include/*.h physics_engine/src/*.cpp)
add_library(PhysicsEngineCommon ${PHYSICS_SRC_FILES})
set_target_properties(PhysicsEngineCommon PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(PhysicsEngineCommon PUBLIC physics_engine/include/)
target_include_directories(PhysicsEngineCommon PUBLIC libs/math/include/)

file(GLOB_RECURSE COMMON_SRC_FILES common/include/*.h common/src/*.cpp)
add_library(Common ${COMMON_SRC_FILES})
set_target_properties(Common PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(Common PUBLIC PhysicsEngineCommon)
target_include_directories(Common PUBLIC common/include/)

file(GLOB_RECURSE SDL_APP_SRC_FILES sdl_application/include/*.h sdl_application/src/*.cpp)
add_library(SDL_AppCommon ${SDL_APP_SRC_FILES})
set_target_properties(SDL_AppCommon PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(SDL_AppCommon PUBLIC sdl_application/include/)
target_link_libraries(SDL_AppCommon PUBLIC Common)
target_link_libraries(SDL_AppCommon PUBLIC SDL2::SDL2)

file(GLOB_RECURSE SAMPLES_SRC_FILES samples/include/*.h samples/src/*.cpp)
add_library(Samples ${SAMPLES_SRC_FILES})
set_target_properties(Samples PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(Samples PUBLIC samples/include/)
target_link_libraries(Samples PUBLIC SDL_AppCommon)

add_executable(PhysicsEngine main.cpp)
target_link_libraries(PhysicsEngine PRIVATE SDL_AppCommon)
target_link_libraries(PhysicsEngine PRIVATE Samples)

# Disable SDL main
add_definitions(-DSDL_MAIN_HANDLED)

# Tests
SET(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)
file(GLOB TEST_FILES ${TEST_DIR}/*.cpp )

foreach(test_file ${TEST_FILES} )
    get_filename_component(test_name ${test_file} NAME_WE)

    IF(test_name STREQUAL RunAllTests)
        continue()
    ENDIF ()

    add_executable(${test_name} ${test_file})

    target_link_libraries(${test_name} PUBLIC SDL_AppCommon)
    target_link_libraries(${test_name} PRIVATE GTest::gtest GTest::gtest_main)

    target_include_directories(${test_name} PUBLIC include/)

    IF(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:AVX2 /Oi /Oy-")
    else()
        set_target_properties(${test_name} PROPERTIES COMPILE_FLAGS "-save-temps -march=haswell -ffast-math -fno-omit-frame-pointer")
    ENDIF()

    set_target_properties (${test_name} PROPERTIES FOLDER Courses)
endforeach()