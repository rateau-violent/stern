# Stern

This project is a C++ 20 library to create backend applications.

## Table of content

1. [Getting Started](#getting-started)
   1. [Choose your HTTP Framework](#choose-your-http-framework)
   2. [Routes](#routes)
   3. [Create your first controller](#create-your-first-controller)
   4. [Create your first module](#create-your-first-module)
   5. [Create an instance of the server](#create-an-instance-of-the-server)
   6. [Link the library to your project](#link-the-library-to-your-project)
2. [Build](#build)
3. [Unit tests](#unit-tests)

## Getting started
The full example is available [here](./example).

### Choose your HTTP Framework
Stern is designed to let you use any Http Framework. You can choose between the one provided with the library, your own 
or any third party library, as long as you provide a framework class that respects the 
[framework concept](./lib/stern/include/stern/framework.h).

Here is an example of framework implementation with the provided http library:
```c++
struct http_framework {
    using method_type = http::methods;
    using response_type = http::response;
    using request_type = http::request;

    static std::string body_to_json(const request_type& req) {
        // Your implementation here
    }

    static std::string query_to_json(const request_type& req) {
        // Your implementation here
    }

    static std::string uri_to_json(const request_type& req) {
        // Your implementation here
    }
};
```

### Routes

Routes are functions that take a `request` as parameter and return a `response` (types of the request and the response
must be specified in the `framework` class).

#### Additional parameters
Your routes can also take additional parameters:
- up to one body parameter structure
- up to one query parameter structure
- up to one uri parameter structure

#### Body parameter

Routes can take body structure parameter, that will retrieve the request's body and reflect it as a structure.

Definition example of a body parameter:
```c++
struct user_dto: stern::parameter::body {
  std::string first_name;
  std::string last_name;
  std::size_t age;
};
```
The structure **MUST** inherit from the `stern::parameter::body` class.

This parameter can then be used by a route:
```c++
http::response user_controller::_post_user(const http::request& req, const user_dto& user) {
    // Your implementation here
}
```

#### Query parameters
:construction: Work in progress :construction:

#### Uri parameters
:construction: Work in progress :construction:

### Create your first controller
A controller is an object that will implement your routes' logic for a certain topic (e.g. you can have a UserController 
for user-related routes, an AccountController for all account-related routes, etc.).

We will be using the following alias: 
```c++
using controller = stern::controller_base<http_framework>;
```

A controller can either be an instance of the `stern::controller_base` class, or inherit from it.
```c++
class main_controller: public controller {
public:
    main_controller();

private:
    http::response _basic_get(const http::request& req);
};
```
This `main_controller` class inherits from the `stern::controller_base` class and implements a single route. 

#### Controller prefix
When creating a new controller class, it is possible to specify a prefix string, that will be added before every path of
the controller's routes. 
For example, when specifying a `user` prefix in a controller, all the controller's routes will be prefixed by the 
`"user/"` string (see [user controller](./example/src/user/user_controller.cpp)).

#### Adding routes to your controller
##### Routes that only take a request as parameter
In order to properly add a route to the controller, the following operation must be performed in the controller's 
constructor:
```c++
emplace_routes({
  { "", http::methods::GET, [this](const http::request& req) { return _basic_get(req); }}
}); 
```
You must specify the route's path and allowed method when adding it to the controller.

##### Additional parameters

For routes that take more than just a request (i.e. body, query or uri parameters), you must specify the additional 
types and parameters when adding the route:
```c++
emplace_route<user_dto>("", http::methods::POST, [this] (const auto& req, const auto& body) {
    return _post_user(req, body);
});
```

### Create your first module

A module is a class that will group one or multiple controllers. A module can also contain one or multiple submodules.

We will be using the following alias:
```c++
using module = stern::module_base<http_framework>;
```

A module can either be an instance of the `stern::module_base` class or inherit from it.
```c++
class main_module: public module {
    public:
        main_module();
};
```

When creating your module, you must specify its controllers and submodules:
```c++
main_module::main_module() {
    _emplace_submodule<user_module>();
    _emplace_controller<main_controller>();
}
```
This main module contains one controller (`main_controller`) and one submodule (`user_submodule`).

### Create an instance of the server

You can create a stern server instance by specifying its port and main module:
```c++
int main() {
  stern::server<example::http_framework> server(3000, example::main_module());

  server.start();

  return 0;
}
```
Once you run the server, it will instanciate all submodules, controllers and routes, and you will be able to make API 
calls.

#### Stopping the server
In order to stop the server, you can either call the `server.stop()` method in your program, or make a `CTRL+C` in the 
console.

### Link the library to your project

In your project's CMakeLists, link the `stern` library to your target:

```cmake
target_link_libraries(example
        stern
)
```

## Build

Init submodules:
```sh
./configure.sh
```

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

---
<center>

[Example](./example/README.md) · [HTTP](./lib/http/README.md) · [Network](./lib/network/README.md)

</center>