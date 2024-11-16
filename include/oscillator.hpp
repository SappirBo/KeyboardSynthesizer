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

    void init_paData();

    void set_wave_table();

    void set_sine_wave_table();
    void set_square_wave_table();
    void set_triabgle_wave_table();
    void set_sawtooth_wave_table();
    void set_empty_table();
public:
    Oscillator(float Hz, WaveType);
    ~Oscillator() = default;

    paData& get_paData();

    void set_freq(float);
    float get_current_freq();
};



#endif