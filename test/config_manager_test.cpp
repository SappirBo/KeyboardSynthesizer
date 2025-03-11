#include <gtest/gtest.h>
#include <filesystem>
#include "config_manager.hpp"

class ConfigManagerTest : public ::testing::Test
{
protected:
    // Called before each test
    void SetUp() override
    {
    }

    // Called after each test
    void TearDown() override {}
private:
    
};

TEST_F(ConfigManagerTest, TestInit)
{
    std::filesystem::path path_to_workdir = "/tmp";
    ConfigManager config_manager = ConfigManager(path_to_workdir);
    
    ASSERT_TRUE(std::filesystem::exists(path_to_workdir / "synthesizer"));
    ASSERT_TRUE(std::filesystem::exists(path_to_workdir / "synthesizer/preset.json"));
    ASSERT_TRUE(std::filesystem::exists(path_to_workdir / "synthesizer/scale_map.json"));
}

TEST_F(ConfigManagerTest, TestLoadNonExistsPreset)
{
    std::filesystem::path path_to_workdir = "/tmp";
    ConfigManager config_manager = ConfigManager(path_to_workdir);

    std::string defualt_preset_name = "default";

    auto preset_data = config_manager.getPresetManager().loadPreset(defualt_preset_name);
    bool is_loaded_defualt_preset{false};
    
    if(preset_data)
    {
        is_loaded_defualt_preset = true;
    }
    ASSERT_TRUE(is_loaded_defualt_preset);

    std::string bad_preset_name = "not-exists";

    preset_data = config_manager.getPresetManager().loadPreset(bad_preset_name);
    bool is_loaded_bad_preset{false};
    
    if(preset_data)
    {
        is_loaded_bad_preset = true;
    }
    ASSERT_FALSE(is_loaded_bad_preset);


}

// TEST_F(ConfigManagerTest, TestLoadDefaultPreset)
// {
//     auto config_manager = ConfigManager("~/.config/synthesizer");
//     auto preset_data_result = config_manager.loadPreset("default");
//     bool is_load_non_exists_preset{false};
//     if(preset_data_result)
//     {
//         const PresetData& data = preset_data_result.value();
//         is_load_non_exists_preset = true;
//     }
//     else
//     {
//         std::cerr << "Error: " << preset_data_result.error() << std::endl;
//     }
//     ASSERT_TRUE(is_load_non_exists_preset);
// }

// TEST_F(ConfigManagerTest, TestSavePreset)
// {
//     ASSERT_TRUE(true);
// }

