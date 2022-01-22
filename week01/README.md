# Week 1 - Data Abstraction: The Walls

This folder contains source code examples managed by a `CMakeLists.txt` file. To build the various targets prescribed by this build system, execute the following commands. Your output will, of course, differ this output, but it will be similar.

```bash
$ cmake -S . -B ./build
-- The C compiler identification is AppleClang 13.0.0.13000029
-- The CXX compiler identification is AppleClang 13.0.0.13000029
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Found Python: /usr/local/Frameworks/Python.framework/Versions/3.9/bin/python3.9 (found version "3.9.9") found components: Interpreter
-- Looking for pthread.h
-- Looking for pthread.h - found
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Success
-- Found Threads: TRUE
-- Configuring done
-- Generating done
-- Build files have been written to: /Users/jdaehn/Source/Repo/msu-csc232-sp22/lectures/build
$
```

NOTE: The `$` shown in these command line terminal windows is merely the command line prompt.

Once `cmake` is run, a `Makefile` is generated that can be used with `make` to generate executables, as shown below.

```bash
$ make -C ./build
[  7%] Building CXX object week01/CMakeFiles/week01.dir/src/main.cpp.o
[ 14%] Linking CXX executable week01
[ 14%] Built target week01
[ 21%] Building CXX object week01/CMakeFiles/week01-demo.dir/src/demo.cpp.o
[ 28%] Linking CXX executable week01-demo
[ 28%] Built target week01-demo
[ 35%] Building CXX object _deps/googletest-build/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o
[ 42%] Linking CXX static library ../../../lib/libgtest.a
[ 42%] Built target gtest
[ 50%] Building CXX object _deps/googletest-build/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o
[ 57%] Linking CXX static library ../../../lib/libgtest_main.a
[ 57%] Built target gtest_main
[ 64%] Building CXX object week01/CMakeFiles/week01-tests.dir/test/test.cpp.o
[ 71%] Linking CXX executable week01-tests
[ 71%] Built target week01-tests
[ 78%] Building CXX object _deps/googletest-build/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o
[ 85%] Linking CXX static library ../../../lib/libgmock.a
[ 85%] Built target gmock
[ 92%] Building CXX object _deps/googletest-build/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o
[100%] Linking CXX static library ../../../lib/libgmock_main.a
[100%] Built target gmock_main
```

The key targets that were built are

1. `week01` - this is often referred to as the "main" target by your instructor as it was built by compiling `src/main.cpp`.
2. `week02-demo` - this is often referred to as the "demo" target by your instructor as it was built by compiling `src/demo.cpp`.
3. `week02-test` - this is often referred to as the "test" target by your instructor as it was built by compiling `test/test.cpp`. This executable will run a GoogleTest suite on your solutions to assess a "program correctness" grade.

Finally, now that we have executables (targets) to run, let's execute them.

```bash
$ ./build/week01/week01
Hello, main!
$./build/week01/week01-demo
Hello, demo!
$ ./build/week01/week01-tests                                                                                   127 ↵
Running main() from /Users/jdaehn/Source/Repo/msu-csc232-sp22/lectures/build/_deps/googletest-src/googletest/src/gtest_main.cc
[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from HelloTest
[ RUN      ] HelloTest.BasicAssertions
[       OK ] HelloTest.BasicAssertions (0 ms)
[----------] 1 test from HelloTest (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (0 ms total)
[  PASSED  ] 1 test.
```
