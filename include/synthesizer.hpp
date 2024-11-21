#include "oscillator.hpp"
#include <mutex>
#include <unordered_map>

class Synthesizer {
private:
  std::vector<Oscillator> m_oscillators;
  paData m_synth_paData;
  float m_synth_freq{16.35};
  std::mutex m_mutex;

public:
  Synthesizer();
  ~Synthesizer();

  void add_oscillator(uint32_t octave, WaveType type);
  void remove_oscillator(size_t index);

  void note_on();
  void note_off();

  paData &get_synth_paData();

  void set_synth_freq(float);

  // Audio callback function
  static int audio_callback(const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo *timeInfo,
                            PaStreamCallbackFlags statusFlags, void *userData);
};

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

void Synthesizer::set_synth_freq(float Hz) {
  m_synth_freq = Hz;
  for (auto &osc : m_oscillators) {
    osc.set_freq(m_synth_freq);
  }
  std::cout << "m_synth_freq = " << m_synth_freq << std::endl;
  for (auto osc : m_oscillators) {
    std::cout << "osc freq = " << osc.get_current_freq() << std::endl;
  }
}

int Synthesizer::audio_callback(const void *inputBuffer, void *outputBuffer,
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
      int indexLeft =
          static_cast<int>(oscData.left_phase) % AudioSettings::TABLE_SIZE;
      int indexRight =
          static_cast<int>(oscData.right_phase) % AudioSettings::TABLE_SIZE;

      float oscSampleLeft = oscData.wave_table[indexLeft];
      float oscSampleRight = oscData.wave_table[indexRight];

      // Sum the samples
      sampleLeft += oscSampleLeft;
      sampleRight += oscSampleRight;

      oscSampleLeft *= osc.get_amplitude();
      oscSampleRight *= osc.get_amplitude();

      // Advance the phase
      oscData.left_phase += oscData.phaseIncrement;
      if (oscData.left_phase >= AudioSettings::TABLE_SIZE)
        oscData.left_phase -= AudioSettings::TABLE_SIZE;

      oscData.right_phase += oscData.phaseIncrement;
      if (oscData.right_phase >= AudioSettings::TABLE_SIZE)
        oscData.right_phase -= AudioSettings::TABLE_SIZE;
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
  for (int i{0}; i < AudioSettings::TABLE_SIZE; ++i) {
    m_synth_paData.wave_table[i] = 0.0f;
  }

  float frac = 1 / m_oscillators.size();

  for (int osc_index{0}; osc_index < m_oscillators.size(); ++osc_index) {
    for (int index{0}; index < AudioSettings::TABLE_SIZE; ++index) {
      m_synth_paData.wave_table[index] =
          frac * m_oscillators.at(osc_index).get_paData().wave_table[index];
    }
  }

  return m_synth_paData;
}