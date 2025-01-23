#ifndef Synthesizer_HPP
#define Synthesizer_HPP

#include "oscillator.hpp"
#include "musical_scale_map.hpp"
#include "portaudio.h"
#include <mutex>
#include <unordered_map>

class Synthesizer {
private:
    std::vector<Oscillator> m_oscillators;
    paData m_synth_paData;
    std::mutex m_mutex;
    float m_synth_freq{16.35};
    float m_synth_glide{0.1};
    float m_attack_time{0.01f};
    float m_deacy_level{0.01f};
    float m_deacy_time{0.01f};
    float m_sustain_time{1.00f};   
    float m_release_time{0.1f};

    MusicScaleMap m_scale_map;  

public:
    Synthesizer();
    ~Synthesizer();

    void add_oscillator(uint32_t octave, WaveType type);
    void remove_oscillator(size_t index);

    void set_glide(float);    

    void set_attack_time(float);
    void set_decay_time(float);
    void set_sustain_time(float);
    void set_release_time(float);
    void set_decay_level(float);
    
    
    float get_attack_time () const;
    float get_decay_time  () const;
    float get_decay_level () const;
    float get_sustain_time() const;
    float get_release_time() const;

    void setSynthKey(std::string);
    void setSynthScale(std::string);
    std::string getSynthKey();
    std::string getSynthScale();
    
    void getConfigAsStrOscilators(std::ostream& oss);
    void getConfigAsStrEnvelop(std::ostream& oss);
    void getConfigAsStr(std::ostream& oss);

    void note_on();
    void note_off();

    paData &get_synth_paData();

    /** insert user input (0-25) into the synth*/
    void insertInput(int);

    void set_synth_freq(float);

    /**Audio callback function */
    static int32_t audio_callback(const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo *timeInfo,
                            PaStreamCallbackFlags statusFlags, void *userData);
};


#endif