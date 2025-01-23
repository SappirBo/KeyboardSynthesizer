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

void PlayLoop::runLoop()
{
    clearConsole();
    std::cout << "Player mode (a-z to play, any other key to exit)\n";
    bool flag{true};
    if (m_audio_player.get()->is_stream_active() == false) {
        m_audio_player.get()->start_stream();
    }

    m_input_handler.get()->inputHandlerOn();
    while (flag) 
    {
        m_input_handler.get()->getInputFromUser();
        if (m_input_handler.get()->getCurrentVal() >= 97 && m_input_handler.get()->getCurrentVal() <= 122) {
            m_synthesizer.get()->insertInput(m_input_handler.get()->getCurrentVal());
            m_synthesizer.get()->note_on();
        } else {
            m_synthesizer.get()->note_off();
            flag = false;
        }
    }
    m_input_handler.get()->inputHandlerOff();
    m_audio_player.get()->stop_stream();
}

