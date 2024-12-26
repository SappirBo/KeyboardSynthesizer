#ifndef PLAY_LOOP_HPP
#define PLAY_LOOP_HPP

#include <iostream>
#include <memory>
#include "base_loop.hpp"
#include "synth_state.hpp"
#include "synthesizer.hpp"
#include "input_handler.hpp"
#include "audio_player.hpp"

class PlayLoop : public BaseLoop
{
private:
    std::shared_ptr<Synthesizer> m_synthesizer;
    std::shared_ptr<InputHandler> m_input_handler;
    std::shared_ptr<AudioPlayer::PortAudioPlayer> m_audio_player;
public:
    PlayLoop(std::shared_ptr<SynthState> state, 
        std::shared_ptr<Synthesizer> synth, 
        std::shared_ptr<InputHandler> input, 
        std::shared_ptr<AudioPlayer::PortAudioPlayer> audio);
    ~PlayLoop();
    void runLoop();
};

#endif