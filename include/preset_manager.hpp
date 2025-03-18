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
    std::vector<std::tuple<std::uint32_t, std::string>> oscillators;

    std::string toString()
    {
        std::string str = "Synth Freq: " + std::to_string(synth_freq) + "\n";
        str += "Synth Glide: " + std::to_string(synth_glide) + "\n";
        str += "Attack Time: " + std::to_string(attack_time) + "\n";
        str += "Deacy Level: " + std::to_string(deacy_level) + "\n";
        str += "Deacy Time: " + std::to_string(deacy_time) + "\n";
        str += "Sustain Time: " + std::to_string(sustain_time) + "\n";
        str += "Release Time: " + std::to_string(release_time) + "\n";
        str += "Scale Map: " + scale_map + "\n";
        str += "Oscillators: \n";
        for (auto osc : oscillators)
        {
            str += "Oscillator: " + std::to_string(std::get<0>(osc)) + " Wave: " + std::get<1>(osc) + "\n";
        }
        return str;
    }
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
    
    std::string getDeafualtPresetName() const;
    void setPresetAsDeafualt(const std::string& preset_name);

private:
    std::filesystem::path m_path_to_synth_folder = "~/.config/synthesizer";
    std::filesystem::path m_path_to_synth_preset = m_path_to_synth_folder / "preset.json";

    std::string m_deafualt_preset = "default";

     /**
     * create workdir/synthesizer/preset.json file
     */
    void createDeafultJson();

    PresetData getDeafualtPreset();

    bool isPresetExists(const std::string& preset_name);
};


#endif // PRESET_MANAGER_HPP