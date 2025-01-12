// tests/test_json_manager.cpp

#include <gtest/gtest.h>
#include <filesystem>
#include "json_manager.hpp"

/**
 * Test fixture for JsonManager tests.
 * You can put common setup/teardown code here if needed.
 */
class JsonManagerTest : public ::testing::Test
{
protected:
    // Called before each test
    void SetUp() override {}

    // Called after each test
    void TearDown() override {}
public:
    std::filesystem::path getPathToProjDir()
    {
         return std::filesystem::current_path().parent_path().parent_path();
    }
};

TEST_F(JsonManagerTest, TestValidJsonFull)
{
    std::filesystem::path path_to_project = getPathToProjDir(); 
    std::filesystem::path path_to_json = path_to_project / "resources/test/test_data.json";
    JsonManager mgr(path_to_json.string());

    std::string result = mgr.toString();

    EXPECT_NE(result.find("\"L1\""), std::string::npos);
    EXPECT_NE(result.find("\"L2\""), std::string::npos);
    EXPECT_NE(result.find("\"Value\""), std::string::npos);
    EXPECT_NE(result.find("\"value\""), std::string::npos);
}


TEST_F(JsonManagerTest, TestInvalidFile)
{
    // Provide a file path that doesn't exist
    JsonManager mgr("non_existent.json");
    

    std::string result = mgr.toString();
    EXPECT_TRUE(result.empty() || result == "{}");
}

TEST_F(JsonManagerTest, TestEmptyPath)
{
    // Provide an empty path, parseJson should fail
    JsonManager mgr("");

    std::string result = mgr.toString(); 
    EXPECT_TRUE(result.empty() || result == "{}");
}
