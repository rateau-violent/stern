## Build

Detect conan profile
```sh
conan profile detect --force
```

Install required packages with conan
```sh
conan install . --output-folder=build --build=missing
```
Setup cmake
```sh
cd build && cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
```
Build the project
```sh
cmake --build .
```

## Unit tests
In order to build and run the unit tests, you must install the [criterion library](https://github.com/Snaipe/Criterion/tree/bleeding).

### Build the unit tests
You must enable unit tests on cmake with the following command:
```sh
cd build && cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DENABLE_TESTS=ON
```
Then, you have to build the project
```sh
cmake --build .
```

### Run the unit tests

Inside the build directory, run:
```sh
ctest
```
