// tests/test_json_manager.cpp

#include <gtest/gtest.h>
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
};

TEST_F(JsonManagerTest, TestValidJsonFull)
{
    // Suppose we have a local JSON file "test_data.json"
    // containing:
    // {
    //   "L1": {
    //     "L2": {
    //       "Value": "value"
    //     }
    //   }
    // }
    //
    // We pass that file path to the JsonManager constructor:
    JsonManager mgr("test_data.json");

    std::string result = mgr.toString();
    // We expect the entire JSON:
    // e.g. {"L1":{"L2":{"Value":"value"}}}
    //
    // Let's just check if it contains known keys
    // (and not worry about the exact JSON formatting).
    EXPECT_NE(result.find("\"L1\""), std::string::npos);
    EXPECT_NE(result.find("\"L2\""), std::string::npos);
    EXPECT_NE(result.find("\"Value\""), std::string::npos);
    EXPECT_NE(result.find("\"value\""), std::string::npos);
}

TEST_F(JsonManagerTest, TestValidJsonNested)
{
    JsonManager mgr("test_data.json");

    std::string l1 = mgr.toString("L1");
    // Expect something like {"L2":{"Value":"value"}}
    EXPECT_NE(l1.find("\"L2\""), std::string::npos);

    std::string l2 = mgr.toString("L1", "L2");
    // Expect something like {"Value":"value"}
    EXPECT_NE(l2.find("\"Value\""), std::string::npos);

    std::string val = mgr.toString("L1", "L2", "Value");
    // Expect something like "value" as a string
    // (or if the library returns a quoted string,
    //  you might see "\"value\"")
    EXPECT_NE(val.find("value"), std::string::npos);
}

TEST_F(JsonManagerTest, TestInvalidFile)
{
    // Provide a file path that doesn't exist
    JsonManager mgr("non_existent.json");
    
    // If the parse fails, we might expect an empty object "{}"
    // or something else based on your logic.
    std::string result = mgr.toString();
    // This might be empty or "{}" if parse failed
    EXPECT_TRUE(result.empty() || result == "{}");
}

TEST_F(JsonManagerTest, TestEmptyPath)
{
    // Provide an empty path, parseJson should fail
    JsonManager mgr("");

    std::string result = mgr.toString(); 
    EXPECT_TRUE(result.empty() || result == "{}");
}
