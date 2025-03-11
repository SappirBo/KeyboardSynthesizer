#ifndef PRESET_MANAGER_HPP
#define PRESET_MANAGER_HPP

#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <expected>
#include <nlohmann/json.hpp>


struct PresetData
{
    float synth_freq;
    float synth_glide;
    float attack_time;
    float deacy_level;
    float deacy_time;
    float sustain_time;   
    float release_time;
    std::string scale_map;
    std::vector<std::tuple<uint32_t, std::string>> oscillators;
};

class PresetManager
{
public:
    PresetManager();
    ~PresetManager();

    void init(std::filesystem::path path_to_synth_folder);

    /**
     * Load preset 'preset_name' 
     */
    std::expected<PresetData, std::string> loadPreset(const std::string& preset_name);

    /**
     * Save preset 'preset_name' with data 'preset_data'
     */
    void savePreset(const std::string& preset_name, const PresetData& preset_data);

    std::vector<std::string> getPresetNames();

private:
    std::filesystem::path m_path_to_synth_folder = "~/.config/synthesizer";
    std::filesystem::path m_path_to_synth_preset = m_path_to_synth_folder / "preset.json";

     /**
     * create workdir/synthesizer/preset.json file
     */
    void createDeafultJson();

    PresetData getDeafualtPreset();

    bool isPresetExists(const std::string& preset_name);
};


#endif // PRESET_MANAGER_HPP