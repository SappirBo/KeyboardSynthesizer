#include <iostream>
#include <unordered_map>
#include <array>
#include "oscillator.hpp"
#include "wave_types.hpp"
#include "audio_player.hpp"
#include "input_handler.hpp"
#include "pa_data.hpp"
#include "audio_settings.hpp"

std::unordered_map<std::string, float> get_key_to_freq_map()
{
    std::unordered_map<std::string, float> key_to_freq;
    key_to_freq["A4"] = 440.000;
    key_to_freq["A#4"] = 466.164;
    key_to_freq["B4"] = 493.883;
    key_to_freq["C5"] = 523.251;
    key_to_freq["C#5"] = 554.3653;
    key_to_freq["D5"] = 587.3295;
    key_to_freq["D#5"] = 622.2540;
    key_to_freq["E5"] = 659.2551;
    key_to_freq["F5"] = 698.4565;
    key_to_freq["F#5"] = 739.9888;
    key_to_freq["G5"] = 783.9909;
    key_to_freq["G#5"] = 830.6094;
    key_to_freq["A5"] = 880.0000;

    return key_to_freq;
}

float get_Hz(int32_t input){
    std::unordered_map<std::string, float> key_to_freq = get_key_to_freq_map();
    std::array<std::string,12> map = {"A4","A#4","B4","C5","C#5","D5","D#5","E5","F5","F#5","G5","G#5"};
    std::string key = map.at(input%12);
    return key_to_freq.at(key);
}

int play_state_loop()
{
    AudioPlayer::PortAudioPlayer audio_player;
    InputHandler input_handler;
    
    float Hz = get_key_to_freq_map()["A4"];

    Oscillator osc{Hz, WaveType::SINE};

    audio_player.Initialize();

    audio_player.set_output_params(2);

    audio_player.open_stream(osc.get_paData());

    audio_player.set_stream_finish();

    bool flag{true};
    while (flag)
    {
        input_handler.get_input_from_user();
        if(input_handler >= 97 && input_handler <=122){  
            if (audio_player.is_stream_active()){
                audio_player.stop_stream();
            }
            Hz = get_Hz(input_handler.get_current_val());
            osc.set_freq(Hz);
            audio_player.start_stream();
        }else{
            flag = false;
            audio_player.stop_stream();
        }
    }

    audio_player.close_stream();

    audio_player.terminate_stream();

    return 0;
}

int configure_system_loop()
{
    return 0;
}

// int synth_engine()
// {

// }
int main(){
    std::cout << "Keyboard Synthesizer Project" << std::endl;
    play_state_loop();
    std::cout << "Keyboard Synthesizer Finished" << std::endl;
    return 0;
}

