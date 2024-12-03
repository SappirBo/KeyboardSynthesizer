#include "audio_player.hpp"
#include "audio_settings.hpp"
#include "input_handler.hpp"
#include "oscillator.hpp"
#include "pa_data.hpp"
#include "synthesizer.hpp"
#include "wave_types.hpp"
#include "synth_engine.hpp"
#include <array>
#include <iostream>
#include <unordered_map>

int32_t main() 
{
  std::cout << "Keyboard Synthesizer Project" << std::endl;
  SynthEngine& synth_engine = SynthEngine::getSynthEngine();
  synth_engine.run();
  std::cout << "Keyboard Synthesizer Finished" << std::endl;
  return 0;
}