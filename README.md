# MicroServices
- By [Ostap Trush](https://github.com/Adeon18)

Some microservices written in C++ as lab works for the Software Architecture Course at Ukrainian Catholic University

## Requirements
- gcc/clang
- cmake
- spdlog
- libhttpserver
- cpr

_Note: cpr, spdlog and libhttpserver can be installed via package managers or by compiling from
source(the libraries are connected as submodules)_

## Building

```
git clone https://github.com/Adeon18/MicroServices.git

git submodule init      # If building libraries from scratch
git submodule update    # if building libraries from scratch

cd MicroServices
mkdir build && cd build
cmake .. && make
```

## Running
Just run 3 executables from separate terminal instances and you're good. You can also use Clion's `Services` interface for that too.
