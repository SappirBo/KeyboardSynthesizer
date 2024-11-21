#ifndef OSCILLATOR_HPP
#define OSCILLATOR_HPP

#include "audio_settings.hpp"
#include "pa_data.hpp"
#include "wave_types.hpp"
#include <cmath>
#include <iostream>
#include <vector>

class Oscillator {
private:
    /** Oscillator Wave type*/
    WaveType m_wave_type;

    /** Current Hz freq (might be in the middle of a glide)*/
    float m_Hz;
    paData m_paData;

    /**Octave of this oscillator */
    int m_octave;

    /**target - what freq is current setted at the  Synth*/
    float m_targetHz;

    /**
     * Portamento (Glide)
     * Smaller Value: Results in a slower glide (longer portamento time).
     * Larger Value : Leads to a faster transition (shorter glide time).
     */
    float m_freqSmoothing{0.01f};

    /**The current amplitude (volume) of the oscillator. */
    float m_amplitude{0.0f};
    /**The desired amplitude the oscillator aims to reach. */
    float m_targetAmplitude{0.0f};

    /**
     *The amplitude smoothing factor for the oscillator.
     *Smaller Value: Results in a slower change (longer attack/release time).
     *Larger Value: Leads to a faster change (shorter attack/release time).
     */
    float m_ampSmoothing{0.000001f};

    void init_paData();

    void set_wave_table();

    void set_sine_wave_table();
    void set_square_wave_table();
    void set_triabgle_wave_table();
    void set_sawtooth_wave_table();
    void set_empty_table();

public:
    Oscillator(float Hz, uint32_t octave, WaveType type);
    ~Oscillator() = default;

    paData &get_paData();

    void set_freq(float);
    void set_octave(uint32_t);
    float get_current_freq();

    void update_freq() {
    float freqDiff = m_targetHz - m_Hz;
    m_Hz += freqDiff * m_freqSmoothing;
    m_paData.phaseIncrement =
        (m_Hz * AudioSettings::TABLE_SIZE) / AudioSettings::SAMPLE_RATE;
    }

    /**
     * Maximum amplitude
     */
    void note_on() { m_targetAmplitude = 1.0f; }


    /**
     * Silence
     */
    void note_off() { m_targetAmplitude = 0.0f; }

    /**
     *  Amplitude Control: according note_on/ note_off
     */
    void update_amplitude() {
        float ampDiff = m_targetAmplitude - m_amplitude;
        m_amplitude += ampDiff * m_ampSmoothing;
    }

    float get_amplitude() const { return m_amplitude; }
};

#endif