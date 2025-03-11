#ifndef SCALE_MANAGER_HPP
#define SCALE_MANAGER_HPP

#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <expected>
#include <nlohmann/json.hpp>


struct ScaleData
{
    ScaleData(std::string scale_name, std::vector<double> scale_intervals)
        : scale_name(scale_name), scale_intervals(scale_intervals) {}
    std::vector<double> scale_intervals;
    std::string scale_name;
};


class ScaleManager
{
public:
    ScaleManager();
    ~ScaleManager();

    void init(std::filesystem::path path_to_synth_folder);

    /**
     * Load scale 'scale_name' 
     */
    std::expected<ScaleData, std::string> loadScale(const std::string& scale_name);

    /**
     * Save scale 'scale_name' with data 'scale_data'
     */
    void saveScale(const ScaleData& scale_data);

    std::vector<std::string> getScalesNames();

private:
    std::filesystem::path m_path_to_synth_folder = "~/.config/synthesizer";
    std::filesystem::path m_path_to_synth_scale_map = m_path_to_synth_folder / "scale_map.json";

     /**
     * create workdir/synthesizer/scale_map.json file
     */
    void createDeafultJson();

    std::vector<ScaleData> getDeafualtScales();

    bool isScaleExists(const std::string& scale_name);
};


#endif // SCALE_MANAGER_HPP