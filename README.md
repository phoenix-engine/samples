# Phoenix Samples

Sections:

- [Setup](#setup)
- [Samples](#samples)

## Setup

To build the Phoenix samples, you need to have [CMake](https://cmake.org/)
installed.

First, make sure to fetch the submodule dependencies:

```sh
$ git submodule update --init --recursive
```

If you already know what build tool you're using, you can skip to the
next section.  Otherwise, open a command line and run `cmake --help` to
see a list of available build generators.

Now, you may create a build for your platform by running the following commands:

```sh
$ cd build
$ cmake -G <your platform> .. -DCMAKE_BUILD_TYPE=Debug
# Where <your platform> is "Visual Studio 16 2019", "NMake Makefiles",
# or "Ninja", for example
$ ninja
# Or "make", "nmake", open in Visual Studio and build, etc.
```

The executables for each sample can then be found in the `build/target`
directory.

## Samples

- [BasicVulkan](basic_vulkan/README.md)
- [BasicPushConstants](basic_pushconstants/README.md)
