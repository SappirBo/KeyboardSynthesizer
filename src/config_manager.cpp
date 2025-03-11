#include "config_manager.hpp"

ConfigManager::ConfigManager(std::filesystem::path path_to_workdir)
: m_path_to_workdir(path_to_workdir)
{
    m_path_to_synth_folder = m_path_to_workdir / "synthesizer";   

    if (!std::filesystem::exists(m_path_to_synth_folder)) {
        // synthesize folder does not exist, create one, and create settings.json with deafult preset
        createSynthesizerFolder();
    }
    
    m_preset_manager.init(m_path_to_synth_folder);
    m_scale_manager.init(m_path_to_synth_folder);
}

ConfigManager::~ConfigManager()
{
}

bool ConfigManager::createSynthesizerFolder()
{
    return std::filesystem::create_directory(m_path_to_synth_folder);
}

