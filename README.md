# Advent of code 2023

![ci-status](https://github.com/NoMore201/advent-of-code-2023/actions/workflows/ci.yml/badge.svg)

My attempt at solving advent of code 2023 challenges with modern C++.

This repository is based on a template generated with the awesome
[cmake-init](https://github.com/friendlyanon/cmake-init) and it uses the following
tools:

- CMake
- vcpkg package manager for dependencies
- Google Test for unit testing
- Support for static analysis (clang-tidy and cppcheck)

It supports MSVC, clang and gcc compilers for both Windows and GNU/Linux.

## Building and installing

### Dependencies

For a list of dependencies, please refer to [vcpkg.json](vcpkg.json).

### Build

This project doesn't require any special command-line flags to build to keep
things simple.

Here are the steps for building in release mode with a single-configuration
generator, like the Unix Makefiles one:

```sh
cmake -S . -B build -D CMAKE_BUILD_TYPE=Release
cmake --build build
```

Here are the steps for building in release mode with a multi-configuration
generator, like the Visual Studio ones:

```sh
cmake -S . -B build
cmake --build build --config Release
```

### Building with MSVC

Note that MSVC by default is not standards compliant and you need to pass some
flags to make it behave properly. See the `flags-windows` preset in the
[CMakePresets.json](CMakePresets.json) file for the flags and with what
variable to provide them to CMake during configuration.


## Developing

For a guide on how to set up the project for local development, refer to the
[HACKING.md](./HACKING.md) file.

## Contributing

Every contribution is welcome. Remember to be respectful.

# Licensing

This project is licensed under the [MIT license](./COPYING).