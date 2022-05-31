[![Coverage Status](https://coveralls.io/repos/github/ATECZER/lab05/badge.svg?branch=main)](https://coveralls.io/github/ATECZER/lab05?branch=main)

## Основываясь на лабораторной работе номер 5

```bash
git clone https://github.com/ATECZER/lab04.git
git remote remove origin
git remote add origin git@github.com:ATECZER/lab05.git
```


```bash
vim CMakeLists.txt
```
```cmake
cmake_minimum_required(VERSION 3.4)

SET(COVERAGE OFF CACHE BOOL "Coverage")
SET(CMAKE_CXX_COMPILER "/usr/bin/g++")

project(tests)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/third-party/gtest" "gtest")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/banking)

add_executable(tests ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp)

if (COVERAGE)
    target_compile_options(tests PRIVATE --coverage)
    target_link_libraries(tests PRIVATE --coverage)
endif()

target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/banking)

target_link_libraries(tests PRIVATE gtest gtest_main gmock_main banking)
```


```yml
name: CMake

on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]

env:
  # Customize the CMake build type here (Release, Debug, RelWithDebInfo, etc.)
  BUILD_TYPE: Release

jobs:
  build:
  
    runs-on: ubuntu-latest

    steps:
    - uses: actions/checkout@v3

    - name: submodules
      run : |
        git submodule update --init --recursive
        sudo apt install lcov
        
    - name: Build
      run: cmake -H. -B _build -DCOVERAGE=1  && cmake --build _build

    - name: Test
      working-directory: ${{github.workspace}}/_build
      # Execute tests defined by the CMake configuration.  
      # See https://cmake.org/cmake/help/latest/manual/ctest.1.html for more detail
      run: |
        ./tests
        lcov -c -t "symmetrictree" -o lcov.info -d .
        lcov --remove lcov.info '/home/runner/work/lab05/lab05/third-party/gtest/*' -o lcov.info
        lcov --remove lcov.info '/usr/include/*' -o lcov.info
        
    - name: CovBeg
      uses: coverallsapp/github-action@master
      with:
          github-token: ${{ secrets.github_token }}
          path-to-lcov: ./_build/lcov.info
          coveralls-endpoint: https://coveralls.io
```
