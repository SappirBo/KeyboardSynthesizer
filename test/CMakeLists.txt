# tests/CMakeLists.txt
cmake_minimum_required(VERSION 3.12)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.12.1  # or another tag
)
# Download and make the googletest project available
FetchContent_MakeAvailable(googletest)

# Now you have GTest::gtest and GTest::gtest_main targets available

# Add the test executable
add_executable(json_manager_test json_manager_test.cpp)

# Link libraries: your source code + Google Test
target_link_libraries(json_manager_test
    PRIVATE
        GTest::gtest
        GTest::gtest_main
        nlohmann_json::nlohmann_json
)

# Google Test-specific CMake function to register tests
include(GoogleTest)
gtest_discover_tests(json_manager_test)
