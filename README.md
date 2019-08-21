# Phoenix Samples

To build the Phoenix samples, you need to have [CMake](https://cmake.org/)
installed.

First, make sure to fetch the submodule dependencies:

```sh
$ git submodule update --init --recursive
```

Now, you may create a build for your platform by running the following commands:

```sh
$ cd build
$ cmake -G <your platform> .. -DCMAKE_BUILD_TYPE=Debug
# Or "Visual Studio 16 2019", for example
$ ninja
# Or "nmake", for example
```

The executables for each sample can then be found in the `build/target`
directory.