#include "oscillator.hpp"

Oscillator::Oscillator(float Hz, uint32_t octave, WaveType type)
    : m_Hz(Hz), m_wave_type(type) {
  set_octave(octave);
  set_wave_table();
  set_freq(m_Hz);
  sprintf(m_paData.message, "No Message");
}

paData &Oscillator::get_paData() { return m_paData; }

void Oscillator::set_octave(uint32_t octave) { m_octave = octave; }

void Oscillator::set_freq(float Hz) {
  m_targetHz = Hz;
  // m_paData.phaseIncrement = (m_Hz* m_octave * AudioSettings::TABLE_SIZE) /
  // AudioSettings::SAMPLE_RATE;
}

float Oscillator::get_current_freq() { return m_Hz; }

void Oscillator::set_wave_table() {
  switch (m_wave_type) {
  case WaveType::SINE:
    set_sine_wave_table();
    break;
  case WaveType::SQUARE:
    set_square_wave_table();
    break;
  case WaveType::SAWTOOTH:
    set_sawtooth_wave_table();
    break;
  case WaveType::TRIANGLE:
    set_triabgle_wave_table();
    break;
  default:
    std::cout << "Unknown Wave Type -> Out." << std::endl;
    break;
  }

  m_paData.left_phase = 0.0;
  m_paData.right_phase = 0.0;
}

void Oscillator::set_sine_wave_table() {
  for (int i = 0; i < AudioSettings::TABLE_SIZE; i++) {
    m_paData.wave_table[i] =
        (float)sin(((float)i / (float)AudioSettings::TABLE_SIZE) * 2.0 *
                   AudioSettings::PI);
  }
}
void Oscillator::set_square_wave_table() {
  for (int i = 0; i < AudioSettings::TABLE_SIZE; i++) {
    double t =
        static_cast<double>(i) / static_cast<double>(AudioSettings::TABLE_SIZE);
    if (t < 0.5)
      m_paData.wave_table[i] = 1.0; // High value
    else
      m_paData.wave_table[i] = -1.0; // Low value
  }
}
void Oscillator::set_triabgle_wave_table() {
  for (int i = 0; i < AudioSettings::TABLE_SIZE; i++) {
    double t =
        static_cast<double>(i) / static_cast<double>(AudioSettings::TABLE_SIZE);
    m_paData.wave_table[i] = 2.0 * fabs(2.0 * t - 1.0) - 1.0;
  }
}
void Oscillator::set_sawtooth_wave_table() {
  for (int i = 0; i < AudioSettings::TABLE_SIZE; i++) {
    double t =
        static_cast<double>(i) / static_cast<double>(AudioSettings::TABLE_SIZE);
    m_paData.wave_table[i] = 2.0 * t - 1.0;
  }
}
void Oscillator::set_empty_table() {
  for (int i = 0; i < AudioSettings::TABLE_SIZE; i++) {
    m_paData.wave_table[i] = 0.0;
  }
}