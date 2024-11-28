#ifndef SYNTH_ENGINE_HPP
#define SYNTH_ENGINE_HPP

#include <iostream>
#include <memory>
#include <sstream>
#include <cstdlib> 
#include "synthesizer.hpp"
#include "input_handler.hpp"
#include "audio_player.hpp"
#include "synth_state.hpp"
#include "main_loop.hpp"
#include "configure_loop.hpp"


/**
 * This class is the engine to all the project, controls the  system flow and active all params.
 */
class SynthEngine
{
private:
    SynthEngine();
    static std::unique_ptr<SynthEngine> m_synth_engine;
    std::unique_ptr<InputHandler> m_input_handler;
    std::unique_ptr<Synthesizer> m_synthesizer;
    std::unique_ptr<AudioPlayer::PortAudioPlayer> m_audio_player;

    std::shared_ptr<SynthState> m_state;

    std::unique_ptr<MainLoop> m_main_loop;
    std::unique_ptr<ConfigureLoop> m_configure_loop;
    
public:
    ~SynthEngine();

    SynthEngine(const SynthEngine&) = delete;// Delete copy constructors
    SynthEngine& operator=(const SynthEngine&) = delete;// Delete move constructors

    static SynthEngine& getSynthEngine() {
        static SynthEngine m_synth_engine;
        return m_synth_engine;
    }

    /**
     * Starts the synth, states:
     * 1. main page
     * - 1.1. play mode
     * - 1.2. configure mode
     * - 1.3. save / load mode
     */
    void run();

    void play_state_loop();
    
    float get_Hz(int32_t input);

    void set_defualt_config();

    void startStream();

    void clear_console();
};

float SynthEngine::get_Hz(int32_t input) {
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

SynthEngine::SynthEngine()
{
    std::cout << "SynthEngine: INIT\n";
    // initializing objects:
    m_synthesizer = std::make_unique<Synthesizer>();
    m_audio_player = std::make_unique<AudioPlayer::PortAudioPlayer>(
        &Synthesizer::audio_callback, 
        m_synthesizer.get()
    );
    m_input_handler = std::make_unique<InputHandler>();

    m_state = std::make_shared<SynthState>(SynthState::Defualt);

    // Set The Player Running
    m_audio_player.get()->Initialize();
    m_audio_player.get()->set_output_params(2);
    m_audio_player.get()->open_stream();
    m_audio_player.get()->set_stream_finish();

    m_main_loop = std::make_unique<MainLoop>(m_state);
    m_configure_loop = std::make_unique<ConfigureLoop>(m_state);

    // Set Defualt Config
    set_defualt_config();
}

SynthEngine::~SynthEngine()
{
    //Close Player
    m_audio_player.get()->close_stream();
    m_audio_player.get()->terminate_stream();
    std::cout << "SynthEngine: Destroy\n";
}

void SynthEngine::run()
{
    std::cout << "Keyboard Synthesizer:" << std::endl;
    *m_state.get() = SynthState::Main;
    while(*m_state.get() != SynthState::Out)
    { 
        std::ostringstream oss;
        m_synthesizer.get()->getConfigAsStr(oss);
        switch (*m_state.get())
        {
        case SynthState::Main:
            m_main_loop.get()->run_loop();
            break;
        case SynthState::Configure:
            m_configure_loop.get()->set_synth_data_stream(oss);
            m_configure_loop.get()->run_loop();
            break;
        case SynthState::Play:
            play_state_loop();
            *m_state.get() = SynthState::Main;
            break;
        default:
            *m_state.get() = SynthState::Main;
            break;
        }
    }
}

void SynthEngine::startStream()
{
    if (m_audio_player.get()->is_stream_active() == false) {
        m_audio_player.get()->start_stream();
    }
}

void SynthEngine::play_state_loop() 
{
    clear_console();
    std::cout << "Player mode (a-z to play, any other key to exit)\n";
    bool flag{true};
    startStream();

    while (flag) {
        m_input_handler.get()->get_input_from_user();
        if (m_input_handler.get()->get_current_val() >= 97 && m_input_handler.get()->get_current_val() <= 122) {
            float Hz = get_Hz(m_input_handler.get()->get_current_val());
            m_synthesizer.get()->set_synth_freq(Hz);
            m_synthesizer.get()->note_on();
        } else {
            m_synthesizer.get()->note_off();
            flag = false;
        }
    }
    m_audio_player.get()->stop_stream();
}

void SynthEngine::clear_console()
{
    system("clear");
}

void SynthEngine::set_defualt_config()
{
    m_synthesizer.get()->add_oscillator(4, WaveType::TRIANGLE);
    m_synthesizer.get()->add_oscillator(5, WaveType::SINE);
    m_synthesizer.get()->add_oscillator(1, WaveType::SINE);
    m_synthesizer.get()->add_oscillator(1, WaveType::TRIANGLE);

    m_synthesizer.get()->set_glide(0.001);

    m_synthesizer.get()->set_attack_time(0.01);
    m_synthesizer.get()->set_decay_level(1);
    m_synthesizer.get()->set_decay_time(0);
    m_synthesizer.get()->set_sustain_time(1);
    m_synthesizer.get()->set_release_time(0.5);
};

#endif