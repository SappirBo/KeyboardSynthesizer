#include "musical_scale_map.hpp"
#include "json_manager.hpp"
#include <iostream>


MusicScaleMap::MusicScaleMap()
{
    setScaleIntervalsMap();
    setKeyToFreq();
    m_current_scale = "major";
    m_current_base_note = "C";
}

MusicScaleMap::~MusicScaleMap()
{
}

void MusicScaleMap::setScaleIntervalsMap()
{
    JsonManager json_manager;
    std::filesystem::path relative_path_to_resource{"/resources/etc/scale_map.json"};
    std::filesystem::path absolute_path_to_root = json_manager.getPathFromRoot(relative_path_to_resource);
    json_manager.setPathToJson(absolute_path_to_root);

    auto data = json_manager.getData();
    
    if (!data.contains("scales") || !data["scales"].is_object()) {
        std::cerr << "[MusicScaleMap] Error: 'scales' object not found in JSON." << std::endl;
        return;
    }
    
    for (auto& [scale_name, intervals_json] : data["scales"].items()) {
        std::vector<double> intervals = intervals_json.get<std::vector<double>>();
        m_scales_interval_map[scale_name] = intervals;
    }
}

void MusicScaleMap::setKeyToFreq()
{
  m_key_to_freq["C"] = 4 * 16.35;
  m_key_to_freq["C#"] = 4 * 17.32;
  m_key_to_freq["D"] = 4 * 18.35;
  m_key_to_freq["D#"] = 4 * 19.45;
  m_key_to_freq["E"] = 4 * 20.60;
  m_key_to_freq["F"] = 4 * 21.83;
  m_key_to_freq["F#"] = 4 * 23.12;
  m_key_to_freq["G"] = 4 * 24.50;
  m_key_to_freq["G#"] = 4 * 25.96;
  m_key_to_freq["A"] = 4 * 27.50;
  m_key_to_freq["A#"] = 4 * 29.14;
  m_key_to_freq["B"] = 4 * 30.87;
}

double MusicScaleMap::getIntervalAsHz(uint input)
{
    int scale_size = m_scales_interval_map[m_current_scale].size();
    double interval{0.0};
    for(int i=0; i<input; ++i)
    {
        interval += m_scales_interval_map[m_current_scale].at(i % scale_size);
    }
    return calculateFrequency(
        m_key_to_freq[m_current_base_note],
        interval
        );
}

double MusicScaleMap::calculateFrequency(double f0, double tonesAbove) {
    double semitones = tonesAbove * 2;
    double freq = f0 * std::pow(2.0, semitones / 12.0);
    return freq;
}

void  MusicScaleMap::setScale(std::string scale)
{
    m_current_scale = scale;
}

void  MusicScaleMap::setKey(std::string key)
{
    m_current_base_note = key;
}

std::string MusicScaleMap::getKey(){return m_current_base_note;}
std::string MusicScaleMap::getScale(){return m_current_scale;}