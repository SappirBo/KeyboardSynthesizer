#include "synth_engine.hpp"
#include "config_manager.hpp"
#include <iostream>

std::filesystem::path getPathToWorkdir() {
  const char* home = std::getenv("HOME");
    if (!home) {
        std::cerr << "HOME environment variable is not set.\n";
        return std::filesystem::path("/tmp");
    }
  
  std::filesystem::path path_to_workdir = std::filesystem::path(home) / ".config" ;
  return path_to_workdir;
};

int32_t main() 
{ 
  std::filesystem::path path_to_workdir = getPathToWorkdir();
  ConfigManager config_manager = ConfigManager(path_to_workdir);  

  SynthEngine& synth_engine = SynthEngine::getSynthEngine();
  synth_engine.run();

  return 0;
}