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
    m_targetHz = Hz * std::pow(2.0f, static_cast<float>(m_octave));;
}

float Oscillator::get_current_freq() { 
  return m_Hz; 
}

void Oscillator::set_wave_table(){
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
  for (int32_t i = 0; i < AudioSettings::TABLE_SIZE; i++) {
    m_paData.wave_table[i] =
        (float)sin(((float)i / (float)AudioSettings::TABLE_SIZE) * 2.0 *
                   AudioSettings::PI);
  }
}

void Oscillator::set_square_wave_table() {
  for (int32_t i = 0; i < AudioSettings::TABLE_SIZE; i++) {
    double t =
        static_cast<double>(i) / static_cast<double>(AudioSettings::TABLE_SIZE);
    if (t < 0.5)
      m_paData.wave_table[i] = 1.0; // High value
    else
      m_paData.wave_table[i] = -1.0; // Low value
  }
}

void Oscillator::set_triabgle_wave_table() {
  for (int32_t i = 0; i < AudioSettings::TABLE_SIZE; i++) {
    double t =
        static_cast<double>(i) / static_cast<double>(AudioSettings::TABLE_SIZE);
    m_paData.wave_table[i] = 2.0 * fabs(2.0 * t - 1.0) - 1.0;
  }
}

void Oscillator::set_sawtooth_wave_table() {
  for (int32_t i = 0; i < AudioSettings::TABLE_SIZE; i++) {
    double t =
        static_cast<double>(i) / static_cast<double>(AudioSettings::TABLE_SIZE);
    m_paData.wave_table[i] = 2.0 * t - 1.0;
  }
}

void Oscillator::set_empty_table() {
  for (int32_t i = 0; i < AudioSettings::TABLE_SIZE; i++) {
    m_paData.wave_table[i] = 0.0;
  }
}

void Oscillator::set_osc_attack_time(float attack_time) {
    m_attack_time = (attack_time > 0.0f) ? attack_time : 0.01f;
}

void Oscillator::set_osc_decay_level(float level)
{
  if(level >= 1.0f){m_decay_level = 1.0f;}
  else if(level <= 0.0f){m_decay_level = 0.0f;}
  else{m_decay_level = level;}
}

void Oscillator::set_osc_decay_time(float decay_time) {
    m_decay_time =  (decay_time > 0.0f) ? decay_time : 0.001f;
}

void Oscillator::set_osc_sustain_time(float sustain_time) {
    m_sustain_time =  (sustain_time > 0.0f) ? sustain_time : 0.001f;

}

void Oscillator::set_osc_release_time(float release_time) {
    m_release_time =  (release_time > 0.0f) ? release_time : 0.001f;
}

void Oscillator::note_on() {
    m_amplitude = 0.0f;
    m_target_amplitude = 1.0f;
    m_envelope_stage = EnvelopeStage::Attack;

    m_amp_increment = (m_target_amplitude) / (m_attack_time * AudioSettings::SAMPLE_RATE);
}

void Oscillator::note_off() {
    m_target_amplitude = 0.0f;
    m_envelope_stage = EnvelopeStage::Release;

    // Calculate amplitude increment for release phase
    m_amp_increment = (m_amplitude) / (m_release_time * AudioSettings::SAMPLE_RATE);
}

void Oscillator::update_amplitude() {
    switch (m_envelope_stage) {
        case EnvelopeStage::Attack:
            m_amplitude += m_amp_increment;
            if (m_amplitude >= m_target_amplitude) {
                m_amplitude = m_target_amplitude;
                m_target_amplitude = m_decay_level;
                m_amp_increment = 1.0f / (m_decay_time * AudioSettings::SAMPLE_RATE);
                m_envelope_stage = EnvelopeStage::Decay;
            }
            break;

        case EnvelopeStage::Decay:
            m_amplitude -= m_amp_increment;
            if (m_amplitude <= m_target_amplitude) {
                m_amplitude = m_target_amplitude;
                m_sustain_counter = 0;
                m_amp_increment = 1.0f / (m_sustain_time * AudioSettings::SAMPLE_RATE);
                m_envelope_stage = EnvelopeStage::Sustain;
            }
            break;

        case EnvelopeStage::Sustain:
            // Hold the amplitude at the target level
            m_sustain_counter += m_amp_increment;
            if(m_sustain_counter >= m_sustain_target){
              m_amp_increment = (m_amplitude) / (m_release_time * AudioSettings::SAMPLE_RATE);
              m_target_amplitude = 0.0;
              m_envelope_stage = EnvelopeStage::Release;
            }
            break;

        case EnvelopeStage::Release:
            m_amplitude -= m_amp_increment;
            if (m_amplitude <= m_target_amplitude) {
                m_amplitude = m_target_amplitude;
                m_envelope_stage = EnvelopeStage::Off;
            }
            break;

        case EnvelopeStage::Off:
            // Ensure amplitude is zero when off
            m_amplitude = 0.0f;
            break;
    }
}

void Oscillator::update_freq() {
    float freqDiff = m_targetHz - m_Hz;
    m_Hz += freqDiff * m_freqSmoothing;
    m_paData.phaseIncrement = (m_Hz * AudioSettings::TABLE_SIZE) / AudioSettings::SAMPLE_RATE;
}

void Oscillator::set_osc_glide(float glide)
{
  m_freqSmoothing = (glide > 0.00001 && glide < 1.0) ? glide : ((glide >= 1.0)? 1.0: 0.0001);
}