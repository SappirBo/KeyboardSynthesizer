#include "synthesizer.hpp"

Synthesizer::Synthesizer() {}

Synthesizer::~Synthesizer() {}

void Synthesizer::add_oscillator(uint32_t octave, WaveType type) {
  m_oscillators.push_back(Oscillator{m_synth_freq, octave, type});
}

void Synthesizer::note_on() {
  std::lock_guard<std::mutex> lock(m_mutex);
  for (auto &osc : m_oscillators) {
    osc.note_on();
  }
}

void Synthesizer::note_off() {
  std::lock_guard<std::mutex> lock(m_mutex);
  for (auto &osc : m_oscillators) {
    osc.note_off();
  }
}

void Synthesizer::set_glide(float glide)
{
  std::lock_guard<std::mutex> lock(m_mutex);
  m_synth_glide = glide;
  for(auto& osc: m_oscillators)
  {
    osc.set_osc_glide(m_synth_glide);
  }
}

void Synthesizer::set_attack_time(float attack_time) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_attack_time = attack_time;
    for (auto& osc : m_oscillators) {
        osc.set_osc_attack_time(m_attack_time);
    }
}

void Synthesizer::set_decay_level(float deacy_level) {
  std::lock_guard<std::mutex> lock(m_mutex);
  m_deacy_level = deacy_level;
  for (auto& osc : m_oscillators) {
      osc.set_osc_decay_level(m_deacy_level);
  }
} 

void Synthesizer::set_decay_time(float deacy_time) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_deacy_time = deacy_time;
    for (auto& osc : m_oscillators) {
        osc.set_osc_decay_time(m_deacy_time);
    }
}

void Synthesizer::set_release_time(float release_time) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_release_time = release_time;

    // Update release time for all oscillators
    for (auto& osc : m_oscillators) {
        osc.set_osc_release_time(release_time);
    }
}

void Synthesizer::set_sustain_time(float sustain_time) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_sustain_time = sustain_time;

    // Update release time for all oscillators
    for (auto& osc : m_oscillators) {
        osc.set_osc_sustain_time(sustain_time);
    }
}

float Synthesizer::get_attack_time () const{return m_attack_time;}
float Synthesizer::get_decay_time  () const{return m_deacy_time;}
float Synthesizer::get_decay_level () const{return m_deacy_time;}
float Synthesizer::get_sustain_time() const{return m_sustain_time;}
float Synthesizer::get_release_time() const{return m_release_time;}


void Synthesizer::set_synth_freq(float Hz) {
  m_synth_freq = Hz;
  for (auto &osc : m_oscillators) {
    osc.set_freq(m_synth_freq);
  }
}

int32_t Synthesizer::audio_callback(const void *inputBuffer, void *outputBuffer,
                                unsigned long framesPerBuffer,
                                const PaStreamCallbackTimeInfo *timeInfo,
                                PaStreamCallbackFlags statusFlags,
                                void *userData) {

  Synthesizer *synth = static_cast<Synthesizer *>(userData);
  float *out = static_cast<float *>(outputBuffer);

  (void)inputBuffer; // Prevent unused variable warnings
  (void)timeInfo;
  (void)statusFlags;

  // Lock the oscillator vector during processing
  std::lock_guard<std::mutex> lock(synth->m_mutex);

  // For each frame
  for (unsigned long i = 0; i < framesPerBuffer; ++i) {
    float sampleLeft = 0.0f;
    float sampleRight = 0.0f;

    // Sum the outputs of all oscillators
    for (auto &osc : synth->m_oscillators) {
      osc.update_freq();      // Smooth frequency change
      osc.update_amplitude(); // Smooth amplitude change
      paData &oscData = osc.get_paData();

      // Get the current sample from the oscillator's wavetable
      int32_t indexLeft  = static_cast<int32_t>(oscData.left_phase)  % AudioSettings::TABLE_SIZE;
      int32_t indexRight = static_cast<int32_t>(oscData.right_phase) % AudioSettings::TABLE_SIZE;

      float oscSampleLeft  = oscData.wave_table[indexLeft ];
      float oscSampleRight = oscData.wave_table[indexRight];

      oscSampleLeft  *= osc.get_amplitude();
      oscSampleRight *= osc.get_amplitude();

      // Sum the samples
      sampleLeft  += oscSampleLeft;
      sampleRight += oscSampleRight;

      // Advance the phase
      oscData.left_phase += oscData.phaseIncrement;
      if (oscData.left_phase >= AudioSettings::TABLE_SIZE){
        oscData.left_phase -= AudioSettings::TABLE_SIZE;
      }

      oscData.right_phase += oscData.phaseIncrement;
      if (oscData.right_phase >= AudioSettings::TABLE_SIZE){
        oscData.right_phase -= AudioSettings::TABLE_SIZE;
      }
    }


    // Normalize the combined sample to prevent clipping
    size_t oscCount = synth->m_oscillators.size();
    if (oscCount > 0) {
      sampleLeft /= static_cast<float>(oscCount);
      sampleRight /= static_cast<float>(oscCount);
    }

    // Output the combined sample
    *out++ = sampleLeft;
    *out++ = sampleRight;
  }

  return paContinue;
}


paData &Synthesizer::get_synth_paData() {
  for (int32_t i{0}; i < AudioSettings::TABLE_SIZE; ++i) {
    m_synth_paData.wave_table[i] = 0.0f;
  }

  float frac = 1 / m_oscillators.size();

  for (int32_t osc_index{0}; osc_index < m_oscillators.size(); ++osc_index) {
    for (int32_t index{0}; index < AudioSettings::TABLE_SIZE; ++index) {
      m_synth_paData.wave_table[index] =
          frac * m_oscillators.at(osc_index).get_paData().wave_table[index];
    }
  }

  return m_synth_paData;
}

void Synthesizer::getConfigAsStr(std::ostream& oss)
{
  std::string space{"    "};
  oss << "Oscilators:\n";
  int i{0};
  for(auto& osc: m_oscillators)
  {
    oss << space << (i++) << ". ";
    osc.getOscDataAsStr(oss);
    oss <<"\n";
  }
  oss << "Amplitude Envelop:\n";
  oss << space << "Attacl (ms):    " << m_attack_time << "\n";
  oss << space << "Decay  (ms):    " << m_deacy_time << "\n";
  oss << space << "Decay  (level): " << m_deacy_level << "\n";
  oss << space << "Sustain (ms):   " << m_sustain_time << "\n";
  oss << space << "Release (ms):   " << m_release_time << "\n";
}