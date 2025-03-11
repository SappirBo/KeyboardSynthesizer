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
#include "play_loop.hpp"


/**
 * This class is the engine to all the project, controls the  system flow and active all params.
 */
class SynthEngine
{
private:
    SynthEngine();
    static std::unique_ptr<SynthEngine> m_synth_engine;
    std::shared_ptr<InputHandler> m_input_handler;
    std::shared_ptr<Synthesizer> m_synthesizer;
    std::shared_ptr<AudioPlayer::PortAudioPlayer> m_audio_player;

    std::shared_ptr<SynthState> m_state;

    std::unique_ptr<MainLoop> m_main_loop;
    std::unique_ptr<ConfigureLoop> m_configure_loop;
    std::unique_ptr<PlayLoop> m_play_loop;
    
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
     * - 1.4. Out
     */
    void run();
    
    void set_defualt_config();

    void clearConsole();
};

SynthEngine::SynthEngine()
{
    std::cout << "SynthEngine: INIT\n";
    // initializing objects:
    m_synthesizer = std::make_shared<Synthesizer>();
    m_audio_player = std::make_shared<AudioPlayer::PortAudioPlayer>(
        &Synthesizer::audio_callback, 
        m_synthesizer.get()
    );
    m_input_handler = std::make_shared<InputHandler>();

    m_state = std::make_shared<SynthState>(SynthState::Defualt);

    // Set The Player Running
    m_audio_player.get()->Initialize();
    m_audio_player.get()->set_output_params(2);
    m_audio_player.get()->open_stream();
    m_audio_player.get()->set_stream_finish();

    // init to the loops
    m_main_loop = std::make_unique<MainLoop>(m_state);
    m_configure_loop = std::make_unique<ConfigureLoop>(m_state, m_synthesizer);
    m_play_loop = std::make_unique<PlayLoop>(m_state, m_synthesizer, m_input_handler, m_audio_player);

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
        switch (*m_state.get())
        {
        case SynthState::Main:
            m_main_loop.get()->runLoop();
            break;
        case SynthState::Configure:
            m_configure_loop.get()->runLoop();
            break;
        case SynthState::Configure_OSC:
            m_configure_loop.get()->setOscLoop();
            break;
        case SynthState::Configure_Envelop:
            m_configure_loop.get()->setEnvelopLoop();
            break;
        case SynthState::Configure_Key_and_Scale:
            m_configure_loop.get()->setKeyAndScaleLoop();
            break;
        case SynthState::Configure_Key:
            m_configure_loop.get()->setKeyLoop();
            break;
        case SynthState::Configure_Scale:
            m_configure_loop.get()->setScaleLoop();
            break;
        case SynthState::Play:
            m_play_loop.get()->runLoop();
            *m_state.get() = SynthState::Main;
            break;
        case SynthState::Save_Load:
            std::cout << "Save/ Load current config\n";
            *m_state.get() = SynthState::Main;
            break;
        default:
            *m_state.get() = SynthState::Main;
            break;
        }
    }
}

void SynthEngine::clearConsole()
{
    system("clear");
}

void SynthEngine::set_defualt_config()
{
    m_synthesizer.get()->add_oscillator(1, WaveType::SINE);

    m_synthesizer.get()->set_glide(0.001);

    m_synthesizer.get()->set_attack_time(0.01);
    m_synthesizer.get()->set_decay_level(1);
    m_synthesizer.get()->set_decay_time(0);
    m_synthesizer.get()->set_sustain_time(1);
    m_synthesizer.get()->set_release_time(0.5);
};

#endif