cmake_minimum_required(VERSION 3.14)
project(bag_interface)

set(SRC_MAIN_FILES
        src/main.cpp)
set(SRC_DEMO_FILES
        src/demo.cpp)
set(SRC_TEST_FILES
        test/test.cpp)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)
set(GOOGLE_TEST_RELEASE "release-1.11.0")


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/${GOOGLE_TEST_RELEASE}.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(week01 ${SRC_MAIN_FILES})
add_executable(week01-demo ${SRC_DEMO_FILES})
add_executable(week01-tests ${SRC_TEST_FILES})

target_link_libraries(
    week01-tests
    gtest_main
)

target_include_directories(week01 PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/src)
target_include_directories(week01-demo PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/src)
target_include_directories(week01-tests PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/src)

message("${CMAKE_CURRENT_LIST_DIR}: ")
message(${CMAKE_CURRENT_LIST_DIR})

include(GoogleTest)
gtest_discover_tests(week01-tests)

# add custom commands that copy data input files to target working directories
add_custom_command(TARGET week01 PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/resource/main_data.txt ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET week01-demo PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/resource/demo_data.txt ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET week01-tests PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/resource/test_data.txt ${CMAKE_CURRENT_BINARY_DIR})
