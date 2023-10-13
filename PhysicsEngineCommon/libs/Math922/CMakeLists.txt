cmake_minimum_required(VERSION 3.22)
project(math)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(benchmark CONFIG REQUIRED)

file(GLOB_RECURSE SRC_FILES include/*.h)
add_library(Common ${SRC_FILES})
set_target_properties(Common PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(Common PUBLIC fmt::fmt)
target_include_directories(Common PUBLIC include)

# Tests
SET(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)
file(GLOB TEST_FILES ${TEST_DIR}/*.cpp)

foreach(test_file ${TEST_FILES} )
    # I used a simple string replace, to cut off .cpp.
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file})
    # Make sure YourLib is linked to each app
    target_link_libraries(${test_name} PUBLIC Common)
    target_link_libraries(${test_name} PRIVATE GTest::gtest GTest::gtest_main)

    IF(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:AVX2 /Oi /Oy-")
    else()
        set_target_properties(${test_name} PROPERTIES COMPILE_FLAGS "-save-temps -march=haswell -ffast-math -fno-omit-frame-pointer")
    ENDIF()

    set_target_properties (${test_name} PROPERTIES FOLDER Courses)
endforeach()

# Benchmarks
#[[
file(GLOB BENCH_FILES benchmarks/*.cpp)

foreach(BENCH_FILE ${BENCH_FILES})
    get_filename_component(BENCH_NAME ${BENCH_FILE} NAME_WE)
    add_executable(${BENCH_NAME} ${BENCH_FILE}
            include/Constantin/CosFunc.h)
    target_link_libraries(${BENCH_NAME} PUBLIC Common)
    target_link_libraries(${BENCH_NAME} PRIVATE benchmark::benchmark benchmark::benchmark_main)
    target_include_directories(${BENCH_NAME} PRIVATE include/)
    if(MSVC)
        target_compile_definitions(${BENCH_NAME} PUBLIC "_USE_MATH_DEFINES")
        target_compile_options(${BENCH_NAME} PUBLIC /arch:AVX2 /Oi /GR- /EHs-c- /FA /Oy- /GL)
        target_link_options(${BENCH_NAME} PUBLIC /LTCG)
    else()
        target_compile_options(${BENCH_NAME} PUBLIC "-march=haswell" "-masm=intel" -fno-rtti -save-temps
                -fno-omit-frame-pointer -flto -ffast-math)
        target_link_options(${BENCH_NAME} PUBLIC -flto)
    endif()

    set_target_properties (${BENCH_NAME} PROPERTIES FOLDER Bench)
endforeach(BENCH_FILE ${BENCH_FILES})]]
