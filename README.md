## Build
```sh
conan install . --output-folder=build --build=missing
```

```sh
cd build && cmake .. -DCMAKE_BUILD_TYPE=Release
```

```sh
cmake --build .
```