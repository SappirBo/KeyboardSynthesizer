#include "oscillator.hpp"
#include <unordered_map>

// std::unordered_map<std::string, float> get_key_to_freq_map()
// {
//     std::unordered_map<std::string, float> key_to_freq;
//     key_to_freq["C"]  = 16.35;
//     key_to_freq["C#"] = 17.32;
//     key_to_freq["D"]  = 18.35;
//     key_to_freq["D#"] = 19.45;
//     key_to_freq["E"]  = 20.60;
//     key_to_freq["F"]  = 21.83;
//     key_to_freq["F#"] = 23.12;
//     key_to_freq["G"]  = 24.50;
//     key_to_freq["G#"] = 25.96;
//     key_to_freq["A"]  = 27.50;
//     key_to_freq["A#"] = 29.14;
//     key_to_freq["B"]  = 30.87;

//     return key_to_freq;
// }

class Synthesizer
{
private:
    std::vector<Oscillator> m_osc_vec;
    paData m_synth_paData;
    float m_synth_freq{16.35};
    
public:
    Synthesizer();
    ~Synthesizer();

    void add_oscillator(uint32_t octave, WaveType type);
    // Oscillator& get_oscillator();
    // void remove_oscillator(size_t osc_index);

    paData &get_synth_paData();

    void set_synth_freq(float);


};

Synthesizer::Synthesizer(){}

Synthesizer::~Synthesizer(){}


void Synthesizer::add_oscillator(uint32_t octave, WaveType type)
{
    m_osc_vec.push_back(Oscillator{m_synth_freq, octave, type});
}

void Synthesizer::set_synth_freq(float Hz)
{
    m_synth_freq = Hz;
    for(auto osc: m_osc_vec)
    {
        osc.set_freq(m_synth_freq);
    }
}

paData & Synthesizer::get_synth_paData()
{
    for(int i{0}; i<AudioSettings::TABLE_SIZE; ++i)
    {
        m_synth_paData.wave_table[i] = 0.0f;
    } 

    float frac = 1 / m_osc_vec.size();

    for(int osc_index{0}; osc_index< m_osc_vec.size(); ++osc_index)
    {
        for(int index{0}; index< AudioSettings::TABLE_SIZE; ++index)
        {
            m_synth_paData.wave_table[index] = frac * m_osc_vec.at(osc_index).get_paData().wave_table[index];
        }
    }

    return m_synth_paData;
}