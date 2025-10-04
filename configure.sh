#!/bin/bash

# init submodules
git submodule update --init --recursive

# reflect-cpp
./vendors/reflect-cpp/vcpkg/bootstrap-vcpkg.sh
