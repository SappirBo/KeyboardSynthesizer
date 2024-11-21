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
  WaveType m_wave_type;
  float m_Hz;
  paData m_paData;
  int m_octave;
  float m_targetHz;

  /**
   * Portamento (Glide)
   * Smaller Value: Results in a slower glide (longer portamento time).
   * Larger Value : Leads to a faster transition (shorter glide time).
   */
  float m_freqSmoothing{0.01f};
  float m_amplitude{0.0f};
  float m_targetAmplitude{0.0f};

  /**
   * Controls how quickly the oscillator's current amplitude (m_amplitude)
   * transitions to the target amplitude (m_targetAmplitude).
   *
   *    Smaller Value:Results in a slower change (longer attack/release time).
   *    Larger Value:Leads to a faster change (shorter attack/release time).
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

  void note_on() { m_targetAmplitude = 1.0f; }

  void note_off() { m_targetAmplitude = 0.0f; }

  void update_amplitude() {
    float ampDiff = m_targetAmplitude - m_amplitude;
    m_amplitude += ampDiff * m_ampSmoothing;
  }

  float get_amplitude() const { return m_amplitude; }
};

#endif