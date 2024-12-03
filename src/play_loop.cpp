#include "play_loop.hpp"

PlayLoop::PlayLoop(std::shared_ptr<SynthState> state, 
        std::shared_ptr<Synthesizer> synth, 
        std::shared_ptr<InputHandler> input, 
        std::shared_ptr<AudioPlayer::PortAudioPlayer> audio)
        :BaseLoop(state), m_synthesizer(synth), m_input_handler(input), m_audio_player(audio)
{
}

PlayLoop::~PlayLoop()
{
}

void PlayLoop::run_loop()
{
    clear_console();
    std::cout << "Player mode (a-z to play, any other key to exit)\n";
    bool flag{true};
    if (m_audio_player.get()->is_stream_active() == false) {
        m_audio_player.get()->start_stream();
    }

    while (flag) {
        m_input_handler.get()->get_input_from_user();
        if (m_input_handler.get()->get_current_val() >= 97 && m_input_handler.get()->get_current_val() <= 122) {
            // float Hz = get_Hz(m_input_handler.get()->get_current_val());
            // m_synthesizer.get()->set_synth_freq(Hz);
            m_synthesizer.get()->insertInput(m_input_handler.get()->get_current_val());
            m_synthesizer.get()->note_on();
        } else {
            m_synthesizer.get()->note_off();
            flag = false;
        }
    }
    m_audio_player.get()->stop_stream();
}

float PlayLoop::get_Hz(int32_t input) {
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
  std::array<std::string, 12> map = {"A",  "A#", "B", "C",  "C#", "D",
                                     "D#", "E",  "F", "F#", "G",  "G#"};
  std::string key = map.at(input % 12);
  return key_to_freq.at(key);
};