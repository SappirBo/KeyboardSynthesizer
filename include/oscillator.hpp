#ifndef OSCILLATOR_HPP
#define OSCILLATOR_HPP

#include "wave_types.hpp"
#include "audio_settings.hpp"
#include "pa_data.hpp"
#include <vector>
#include <cmath>
#include <iostream>

class Oscillator
{
private:
    WaveType m_wave_type;
    float m_Hz;
    paData m_paData;
    int m_octave;

    void init_paData();

    void set_wave_table();

    void set_sine_wave_table();
    void set_square_wave_table();
    void set_triabgle_wave_table();
    void set_sawtooth_wave_table();
    void set_empty_table();
public:
    Oscillator(float Hz, uint32_t octave,  WaveType type);
    ~Oscillator() = default;

    paData& get_paData();

    void set_freq(float);
    void set_octave(uint32_t);
    float get_current_freq();
};



#endif