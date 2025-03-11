#include "preset_manager.hpp"


PresetManager::PresetManager()
{
}

PresetManager::~PresetManager()
{
}

void PresetManager::init(std::filesystem::path path_to_synth_folder)
{
    m_path_to_synth_folder = path_to_synth_folder;
    m_path_to_synth_preset = m_path_to_synth_folder / "preset.json";

    if (!std::filesystem::exists(m_path_to_synth_preset)) {
        createDeafultJson();
    }
}

void PresetManager::createDeafultJson()
{
    PresetData default_preset = getDeafualtPreset();
    savePreset("default", default_preset);
}

void PresetManager::savePreset(const std::string& preset_name, const PresetData& preset_data)
{
    nlohmann::json presets;

    std::ifstream in_file(m_path_to_synth_preset);
    if (in_file) {
        try {
            in_file >> presets;
        } catch ( nlohmann::json::parse_error& e) {
            std::cerr << "Error parsing JSON file: " << e.what() << "\n";
            presets =  nlohmann::json::object();    // Initialize as empty JSON object if parsing fails.
        }
    }
    in_file.close();

    nlohmann::json preset_json;

    preset_json["Synth-settings"] = {
        {"synth_freq", preset_data.synth_freq},
        {"synth_glide", preset_data.synth_glide},
        {"attack_time", preset_data.attack_time},
        {"deacy_level", preset_data.deacy_level},
        {"deacy_time", preset_data.deacy_time},
        {"sustain_time", preset_data.sustain_time},
        {"release_time", preset_data.release_time},
        {"scale_map", preset_data.scale_map}
    };

    nlohmann::json osc_array = nlohmann::json::array();
    for (const auto& osc : preset_data.oscillators) {
        uint32_t octave;
        std::string waveType;
        std::tie(octave, waveType) = osc;
        osc_array.push_back({
            {"Octave", octave},
            {"WaveType", waveType}
        });
    }
    preset_json["Synth-oscillators"] = osc_array;

    presets[preset_name] = preset_json;

    std::ofstream out_file(m_path_to_synth_preset);
    if (!out_file) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }
    out_file << presets.dump(4);
    out_file.close();
}

PresetData PresetManager::getDeafualtPreset()
{
    PresetData default_preset;

    default_preset.synth_freq = 16.35f;
    default_preset.synth_glide = 0.001f;
    default_preset.attack_time = 1.0f;
    default_preset.deacy_level = 1.0f;
    default_preset.deacy_time = 0.0f;
    default_preset.sustain_time = 1.0f;
    default_preset.release_time = 0.5f;
    default_preset.scale_map = "major";

    default_preset.oscillators = {
        {1, "Sine"}
    };

    return default_preset;
}

std::vector<std::string> PresetManager::getPresetNames()
{
    nlohmann::json presets;

    std::ifstream in_file(m_path_to_synth_preset);
    if (in_file) {
        try {
            in_file >> presets;
        } catch ( nlohmann::json::parse_error& e) {
            std::cerr << "Error parsing JSON file: " << e.what() << "\n";
            presets =  nlohmann::json::object();    // Initialize as empty JSON object if parsing fails.
        }
    }
    in_file.close();

    std::vector<std::string> preset_names;
    for (auto it = presets.begin(); it != presets.end(); ++it) {
        preset_names.push_back(it.key());
    }

    return preset_names;
}

std::expected<PresetData, std::string> PresetManager::loadPreset(const std::string& preset_name)
{
    std::vector<std::string> preset_names = getPresetNames();
    if (std::find(preset_names.begin(), preset_names.end(), preset_name) == preset_names.end())
    {
        return std::unexpected("Preset does not exist.");
    }

    nlohmann::json presets;
    std::ifstream in_file(m_path_to_synth_preset);
    if (in_file) {
        try {
            in_file >> presets;
        } catch ( nlohmann::json::parse_error& e) {
            std::cerr << "Error parsing JSON file: " << e.what() << "\n";
            presets =  nlohmann::json::object();    // Initialize as empty JSON object if parsing fails.
        }
    }
    in_file.close();

    PresetData preset_data;
    nlohmann::json preset_json = presets[preset_name];
    
    preset_data.synth_freq = preset_json["Synth-settings"]["synth_freq"];
    preset_data.synth_glide = preset_json["Synth-settings"]["synth_glide"];
    preset_data.attack_time = preset_json["Synth-settings"]["attack_time"]; 
    preset_data.deacy_level = preset_json["Synth-settings"]["deacy_level"];
    preset_data.deacy_time = preset_json["Synth-settings"]["deacy_time"];
    preset_data.sustain_time = preset_json["Synth-settings"]["sustain_time"];
    preset_data.release_time = preset_json["Synth-settings"]["release_time"];
    preset_data.scale_map = preset_json["Synth-settings"]["scale_map"];

    preset_data.oscillators.clear();
    for (const auto& osc : preset_json["Synth-oscillators"]) {
        preset_data.oscillators.push_back({
            osc["Octave"],
            osc["WaveType"]
        });
    }

    return preset_data;
}
