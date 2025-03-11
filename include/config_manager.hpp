#ifndef CONFIG_MANAGER_HPP
#define CONFIG_MANAGER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <expected>
#include <tuple>
#include <filesystem>
#include "preset_manager.hpp"
#include "scale_manager.hpp"

class ConfigManager
{
public:
    /**
     * path is a path to the folder where the configuration files are stored
     * 
     * constructor will check if path_to_workdir/synthesizer folder exists (if not, creates it), then check 
     * if workdir/synthesizer/settings.json exists ,if not, creates it, (in case of ).
     */
    ConfigManager(std::filesystem::path path_to_workdir = "~/.config");
    ~ConfigManager();

    PresetManager& getPresetManager() { return m_preset_manager; }

    ScaleManager& getScaleManager() { return m_scale_manager; } 

private:
    std::filesystem::path m_path_to_workdir;
    std::filesystem::path m_path_to_synth_folder;

    PresetManager m_preset_manager;
    ScaleManager m_scale_manager;

    /**
     * create ~/.config/synthesizer folder  
     */
    bool createSynthesizerFolder();


    bool isPresetExists(const std::string& preset_name);
};

#endif // CONFIG_MANAGER_HPP