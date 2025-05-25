#!/bin/bash

# init submodules
git submodule update --init --recursive

# reflect-cpp
./vendors/reflect-cpp/vcpkg/bootstrap-vcpkg.sh
#cd ./vendors/reflect-cpp/ \
#  && cmake -S . -B ../../build -DCMAKE_CXX_STANDARD=20 -DREFLECTCPP_AVRO=ON -DREFLECTCPP_BSON=ON -DREFLECTCPP_CAPNPROTO=ON -DREFLECTCPP_CBOR=ON -DREFLECTCPP_FLEXBUFFERS=ON -DREFLECTCPP_MSGPACK=ON -DREFLECTCPP_XML=ON -DREFLECTCPP_TOML=ON -DREFLECTCPP_UBJSON=ON -DREFLECTCPP_YAML=ON -DCMAKE_BUILD_TYPE=Release -DREFLECT_CPP_C_ARRAYS_OR_INHERITANCE=ON \
#  && cmake  --build ../../build -j4
