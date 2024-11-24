#include "audio_player.hpp"
#include "audio_settings.hpp"
#include "input_handler.hpp"
#include "oscillator.hpp"
#include "pa_data.hpp"
#include "synthesizer.hpp"
#include "wave_types.hpp"
#include <array>
#include <iostream>
#include <unordered_map>

std::unordered_map<std::string, float> get_key_to_freq_map() {
  std::unordered_map<std::string, float> key_to_freq;
  key_to_freq["C"] = 4 * 16.35;
  key_to_freq["C#"] = 4 * 17.32;
  key_to_freq["D"] = 4 * 18.35;
  key_to_freq["D#"] = 4 * 19.45;
  key_to_freq["E"] = 4 * 20.60;
  key_to_freq["F"] = 4 * 21.83;
  key_to_freq["F#"] = 4 * 23.12;
  key_to_freq["G"] = 4 * 24.50;
  key_to_freq["G#"] = 4 * 25.96;
  key_to_freq["A"] = 4 * 27.50;
  key_to_freq["A#"] = 4 * 29.14;
  key_to_freq["B"] = 4 * 30.87;

  return key_to_freq;
}

float get_Hz(int32_t input) {
  std::unordered_map<std::string, float> key_to_freq = get_key_to_freq_map();
  std::array<std::string, 12> map = {"A",  "A#", "B", "C",  "C#", "D",
                                     "D#", "E",  "F", "F#", "G",  "G#"};
  std::string key = map.at(input % 12);
  return key_to_freq.at(key);
};

int32_t play_state_loop() {
  InputHandler input_handler;
  Synthesizer syn;
  AudioPlayer::PortAudioPlayer audio_player(&Synthesizer::audio_callback, &syn);

  syn.add_oscillator(4, WaveType::TRIANGLE);
  syn.add_oscillator(5, WaveType::SINE);
  syn.add_oscillator(1, WaveType::SINE);
  syn.add_oscillator(1, WaveType::TRIANGLE);

  syn.set_glide(0.001);

  syn.set_attack_time(0.01);
  syn.set_decay_level(0.5);
  syn.set_decay_time(0.1);
  syn.set_sustain_time(0.3);
  syn.set_release_time(0.8);


  audio_player.Initialize();

  audio_player.set_output_params(2);

  audio_player.open_stream();

  audio_player.set_stream_finish();

  bool flag{true};
  while (flag) {
  input_handler.get_input_from_user();
  if (input_handler >= 97 && input_handler <= 122) {
      if (audio_player.is_stream_active() == false) {
      audio_player.start_stream();
      }
      float Hz = get_Hz(input_handler.get_current_val());
      syn.set_synth_freq(Hz);
      syn.note_on();
  } else {
      syn.note_off();
      flag = false;
      audio_player.stop_stream();
  }
  }

  audio_player.close_stream();

  audio_player.terminate_stream();

  return 0;
}

int32_t configure_system_loop() { return 0; }

// int32_t synth_engine()
// {

// }
int32_t main() {
  std::cout << "Keyboard Synthesizer Project" << std::endl;
  play_state_loop();
  std::cout << "Keyboard Synthesizer Finished" << std::endl;
  return 0;
}