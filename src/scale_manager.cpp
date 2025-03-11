#include "scale_manager.hpp"


ScaleManager::ScaleManager()
{
}

ScaleManager::~ScaleManager()
{
}

void ScaleManager::init(std::filesystem::path path_to_synth_folder)
{
    m_path_to_synth_folder = path_to_synth_folder;
    m_path_to_synth_scale_map = m_path_to_synth_folder / "scale_map.json";

    if (!std::filesystem::exists(m_path_to_synth_scale_map)) {
        createDeafultJson();
    }
}

void ScaleManager::createDeafultJson()
{
    std::vector<ScaleData> default_Scales = getDeafualtScales();
    for(const auto& scale: default_Scales)
    {
        saveScale(scale);
    }
}

void ScaleManager::saveScale(const ScaleData& scale_data)
{
    nlohmann::json scales;

    std::ifstream in_file(m_path_to_synth_scale_map);
    if (in_file) {
        try {
            in_file >> scales;
        } catch ( nlohmann::json::parse_error& e) {
            std::cerr << "Error parsing JSON file: " << e.what() << "\n";
            scales =  nlohmann::json::object();    // Initialize as empty JSON object if parsing fails.
        }
    }
    in_file.close();

    scales[scale_data.scale_name] = scale_data.scale_intervals;

    std::ofstream out_file(m_path_to_synth_scale_map);
    if (!out_file) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }
    out_file << scales.dump(4);
    out_file.close();
}

std::vector<ScaleData> ScaleManager::getDeafualtScales()
{
    std::vector<ScaleData> scales_vector;
    scales_vector.push_back({"major" ,{1,1,0.5,1,1,1,0.5}});
    scales_vector.push_back({"Minor_Pentatonic" ,{1.5,1,1,1.5,1}});
    scales_vector.push_back({"Major_Pentatonic" ,{1,1,1.5,1,1.5}});
    scales_vector.push_back({"Blues" ,{1.5,1,0.5,0.5,1.5,1}});
    scales_vector.push_back({"Diminished" ,{1,0.5,1,0.5,1,0.5,1,0.5}});
    scales_vector.push_back({"Natural_Minor" ,{1,0.5,1,1,0.5,1,1}});
    scales_vector.push_back({"Melodic_Minor" ,{1,0.5,1,1,1,1,0.5}});
    scales_vector.push_back({"Harmonic_Minor" ,{1,0.5,1,1,0.5,1.5,1}});
    scales_vector.push_back({"Dorian_Scale" ,{1,0.5,1,1,1,0.5,1}});
    scales_vector.push_back({"Phrygian_Scale" ,{0.5,1,1,1,0.5,1,1}});
    scales_vector.push_back({"Lydian_Scale" ,{1,1,1,0.5,1,1,0.5}});
    scales_vector.push_back({"Mixolydian_Scale" ,{1,1,0.5,1,1,0.5,1}});

    return scales_vector;
}

std::vector<std::string> ScaleManager::getScalesNames()
{
    nlohmann::json scales;

    std::ifstream in_file(m_path_to_synth_scale_map);
    if (in_file) {
        try {
            in_file >> scales;
        } catch ( nlohmann::json::parse_error& e) {
            std::cerr << "Error parsing JSON file: " << e.what() << "\n";
            scales =  nlohmann::json::object();    // Initialize as empty JSON object if parsing fails.
        }
    }
    in_file.close();

    std::vector<std::string> scales_names;
    for (auto it = scales.begin(); it != scales.end(); ++it) {
        scales_names.push_back(it.key());
    }

    return scales_names;
}

// std::expected<PresetData, std::string> ScaleManager::loadPreset(const std::string& preset_name)
// {
//     std::vector<std::string> preset_names = getPresetNames();
//     if (std::find(preset_names.begin(), preset_names.end(), preset_name) == preset_names.end())
//     {
//         return std::unexpected("Preset does not exist.");
//     }

//     nlohmann::json presets;
//     std::ifstream in_file(m_path_to_synth_preset);
//     if (in_file) {
//         try {
//             in_file >> presets;
//         } catch ( nlohmann::json::parse_error& e) {
//             std::cerr << "Error parsing JSON file: " << e.what() << "\n";
//             presets =  nlohmann::json::object();    // Initialize as empty JSON object if parsing fails.
//         }
//     }
//     in_file.close();

//     PresetData preset_data;
//     nlohmann::json preset_json = presets[preset_name];
    
//     preset_data.synth_freq = preset_json["Synth-settings"]["synth_freq"];
//     preset_data.synth_glide = preset_json["Synth-settings"]["synth_glide"];
//     preset_data.attack_time = preset_json["Synth-settings"]["attack_time"]; 
//     preset_data.deacy_level = preset_json["Synth-settings"]["deacy_level"];
//     preset_data.deacy_time = preset_json["Synth-settings"]["deacy_time"];
//     preset_data.sustain_time = preset_json["Synth-settings"]["sustain_time"];
//     preset_data.release_time = preset_json["Synth-settings"]["release_time"];
//     preset_data.scale_map = preset_json["Synth-settings"]["scale_map"];

//     preset_data.oscillators.clear();
//     for (const auto& osc : preset_json["Synth-oscillators"]) {
//         preset_data.oscillators.push_back({
//             osc["Octave"],
//             osc["WaveType"]
//         });
//     }

//     return preset_data;
// }
