ldl
================================

Building
---------------------------------
### Linux
* Dependencies
To build the tools and samples you only need a lua-dev install.

* Compiling in release mode

```bash
cd ldl
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS_RELEASE="-Wall -O2"  -DCMAKE_C_FLAGS_RELEASE="-Wall -O2" ..
```
* Compiling in debug mode

```bash
cd ldl
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS_RELEASE="-Wall -ggdb"  -DCMAKE_C_FLAGS_RELEASE="-Wall -ggdb" ..
```

### Windows

Soon

### MacOSX

Soon

Running
---------------------------------
### Linux

* tools/ldlread

```bash
ldlread -hlv <ldl file>
```
