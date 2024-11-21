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
    int32_t m_octave;

    /**target - what freq is current setted at the  Synth*/
    float m_targetHz;

    /**
     * Portamento (Glide)
     * Smaller Value: Results in a slower glide (longer portamento time).
     * Larger Value : Leads to a faster transition (shorter glide time).
     */
    float m_freqSmoothing{0.1f};

    /**The current amplitude (volume) of the oscillator. */
    float m_amplitude{0.0f};
    /**The desired amplitude the oscillator aims to reach. */
    float m_target_amplitude{0.0f};

    /**
     *The amplitude smoothing factor for the oscillator.
     *Smaller Value: Results in a slower change (longer attack/release time).
     *Larger Value: Leads to a faster change (shorter attack/release time).
     */
    float m_ampSmoothing{0.000001f};

    /**Attack time in seconds */
    float m_attack_time{0.01f};

    /**Release time in seconds */
    float m_release_time{0.1f};
    
    /**Amplitude increment per sample */
    float m_amp_increment{0.0f};   

    enum class EnvelopeStage { Off, Attack, Sustain, Release };
    EnvelopeStage m_envelope_stage{EnvelopeStage::Off};

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
        m_paData.phaseIncrement = (m_Hz * AudioSettings::TABLE_SIZE) / AudioSettings::SAMPLE_RATE;
    }

    /**
     * Maximum amplitude
     */
    void note_on();

    /**
     * Silence
     */
    void note_off();

    void set_osc_attack_time(float attackTime);
    void set_release_time(float releaseTime);

    /**
     *  Amplitude Control: according note_on/ note_off
     */
    void update_amplitude();

    float get_amplitude() const { return m_amplitude; }
};

#endif