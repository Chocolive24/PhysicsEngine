cmake_minimum_required(VERSION 3.22)
project(PhysicsEngine)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

# Add a CMake option to enable or disable Tracy Profiler
option(USE_TRACY "Use Tracy Profiler" OFF)

if (USE_TRACY)
    # Enable Tracy profiling by setting the preprocessor directive
    add_compile_definitions(TRACY_ENABLE)
    # Include Tracy's headers for the entire project
    include_directories(externals/tracy_profiler/tracy)

    # Add the Tracy source code as part of the project
    add_library(tracyClient STATIC externals/tracy_profiler/TracyClient.cpp)
endif()

option(ENABLE_ADDRESS_SANITIZER "Enable AddressSanitizer" OFF)

IF(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:AVX2 /Oi /Oy-")

    # Check if AddressSanitizer is enabled
    if(ENABLE_ADDRESS_SANITIZER)
        # Enable AddressSanitizer flags and options
        add_compile_options(/fsanitize=address /DEBUG)
    endif()
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -save-temps -march=haswell -ffast-math")

    # Check if AddressSanitizer is enabled
    if(ENABLE_ADDRESS_SANITIZER)
        # Enable AddressSanitizer flags and options
        add_compile_options(-fsanitize=address)
    endif()
ENDIF()

# Create the Math library
file(GLOB_RECURSE MATH_SRC_FILES libs/math/include/*.h libs/math/src/*.cpp)
add_library(math ${MATH_SRC_FILES})
set_target_properties(math PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(math PUBLIC libs/math/include/)

# Create the Common library with Math as a dependency
file(GLOB_RECURSE COMMON_SRC_FILES common/include/*.h common/src/*.cpp)
add_library(common ${COMMON_SRC_FILES})
set_target_properties(common PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(common PUBLIC common/include/)
target_link_libraries(common PRIVATE math)

# Create the PhysicsEngineCommon library with Math as a dependency
file(GLOB_RECURSE PHYSICS_SRC_FILES physics_engine/include/*.h physics_engine/src/*.cpp)
add_library(physics ${PHYSICS_SRC_FILES})
set_target_properties(physics PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(physics PUBLIC physics_engine/include/)
target_include_directories(math PUBLIC libs/math/include/)
target_link_libraries(physics PRIVATE math common)

if (USE_TRACY)
    target_compile_definitions(physics PUBLIC TRACY_ENABLE)
    # Link the TracyClient library
    target_link_libraries(physics PRIVATE tracyClient)
endif()

# Create the SDL_AppCommon library with Math as a dependency
file(GLOB_RECURSE SDL_APP_SRC_FILES sdl_application/include/*.h sdl_application/src/*.cpp)
add_library(graphics ${SDL_APP_SRC_FILES})
set_target_properties(graphics PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(graphics PUBLIC sdl_application/include/)
target_link_libraries(graphics PRIVATE $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static> math common imgui::imgui)

# Create the samples library with dependencies on PhysicsEngineCommon, SDL_AppCommon, Common, and Math
file(GLOB_RECURSE samples_SRC_FILES samples/include/*.h samples/src/*.cpp)
add_library(samples ${samples_SRC_FILES})
set_target_properties(samples PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(samples PUBLIC samples/include/)
target_link_libraries(samples PRIVATE physics graphics common math imgui::imgui)
if (USE_TRACY)
    target_compile_definitions(samples PUBLIC TRACY_ENABLE)
    # Link the TracyClient library
    target_link_libraries(samples PRIVATE tracyClient)
endif()

# Create the PhysicsEngine executable with the samples library as a dependency
add_executable(main main.cpp)
target_link_libraries(main PRIVATE physics graphics common math imgui::imgui samples)
if (USE_TRACY)
    target_compile_definitions(main PUBLIC TRACY_ENABLE)
    # Link the TracyClient library
    #target_link_libraries(main PRIVATE tracyClient)
endif()

# Tests physics library.
file(GLOB_RECURSE PHYSICS_TEST_FILES physics_engine/tests/*.cpp)
foreach(test_file ${PHYSICS_TEST_FILES} )
    get_filename_component(test_name ${test_file} NAME_WE)

    add_executable(${test_name} ${test_file})

    target_link_libraries(${test_name} PRIVATE physics common math)
    target_link_libraries(${test_name} PRIVATE GTest::gtest GTest::gtest_main)
endforeach()


# Tests common library.
file(GLOB_RECURSE COMMON_TEST_FILES common/tests/*.cpp)
foreach(test_file ${COMMON_TEST_FILES} )
    get_filename_component(test_name ${test_file} NAME_WE)

    add_executable(${test_name} ${test_file})

    target_link_libraries(${test_name} PRIVATE common math)
    target_link_libraries(${test_name} PRIVATE GTest::gtest GTest::gtest_main)
endforeach()