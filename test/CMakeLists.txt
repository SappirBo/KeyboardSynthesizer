# tests/CMakeLists.txt
cmake_minimum_required(VERSION 3.12)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.12.1  # or another tag
)
FetchContent_MakeAvailable(googletest)

#############################################
# Test for Json Manager
#############################################
add_executable(json_manager_test json_manager_test.cpp)
target_link_libraries(json_manager_test
    PRIVATE
        GTest::gtest
        GTest::gtest_main
        nlohmann_json::nlohmann_json
)
include(GoogleTest)
gtest_discover_tests(json_manager_test)



#############################################
# Test for Config Manager
#############################################
add_executable(config_manager_test config_manager_test.cpp)
target_link_libraries(config_manager_test
    PRIVATE
        GTest::gtest
        GTest::gtest_main
        nlohmann_json::nlohmann_json
        ConfigManager
)
include(GoogleTest)
gtest_discover_tests(config_manager_test)