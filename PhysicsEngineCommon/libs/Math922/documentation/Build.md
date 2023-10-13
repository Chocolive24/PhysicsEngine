[Return](../README.md)

# Build

## CLion

- Go to `File` -> `Settings` -> `Build, Execution, Deployment` -> `Toolchains` -> `+` -> `System`

![clion toolchains](images/clion_toolchains.png)

1. Go to `File` -> `Settings` -> `Build, Execution, Deployment` -> `CMake` -> add a new profile with the toolchain you just created named `Debug`
2. Set `CMake options` to `-DCMAKE_TOOLCHAIN_FILE=<path to vcpkg>/scripts/buildsystems/vcpkg.cmake`

![clion cmake](images/clion_cmake.png)

- Go to `CMakeLists.txt` and reload it