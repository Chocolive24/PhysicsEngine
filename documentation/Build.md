[Return](../README.md)

# Build

## Visual Studio

- Open CMake https://cmake.org/download/

![CMake build](images/visual_studio_cmake.png)

- Step 1: Enter Path to project

- Step 2: Enter Path to Build (create a new empty folder if doesn't exists already)

- Step 3: Press `Generate`

- Step 4: Select `Specify toolchain for cross-compiling`

- Step 5: Press `Next`

- Step 6: Enter Path to vcpkg.cmake https://github.com/microsoft/vcpkg

- Step 7: Press `Finish`

- Step 8: Press `Open Project` (if it does nothing, go to `Build` and Open `Bark.sln` with `Visual Studio`)

![Setup Project](images/visual_studio_setup.png)

- Step 9: Right click on `Main`

- Step 10: Press `Set as Startup Project`

- You can now navigate through the samples using the `ImGui` window or with `keyboard arrows` use the `Space key` to regenerate a Sample.



## CLion

- Go to `File` -> `Settings` -> `Build, Execution, Deployment` -> `Toolchains` -> `+` -> `System`

![clion toolchains](images/clion_toolchains.png)

1. Go to `File` -> `Settings` -> `Build, Execution, Deployment` -> `CMake` -> add a new profile with the toolchain you just created named `Debug`
2. Set `CMake options` to `-DCMAKE_TOOLCHAIN_FILE="<path to vcpkg>/scripts/buildsystems/vcpkg.cmake"`,

![clion cmake](images/clion_cmake.png)

- Go to `CMakeLists.txt` and reload it