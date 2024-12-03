#include "musical_scale_map.hpp"
#include <iostream>


MusicScaleMap::MusicScaleMap()
{
    setScaleIntervalsMap();
    setKeyToFreq();
    m_current_scale = "major";
    m_current_base_note = "C";
}

MusicScaleMap::~MusicScaleMap()
{
}

void MusicScaleMap::setScaleIntervalsMap()
{
    m_scales_interval_map["major"]            = {1,1,0.5,1,1,1,0.5};
    m_scales_interval_map["Minor_Pentatonic"] = {1.5,1,1,1.5,1};
    m_scales_interval_map["Major_Pentatonic"] = {1,1,1.5,1,1.5};
    m_scales_interval_map["Blues"]            = {1.5,1,0.5,0.5,1.5,1};
    m_scales_interval_map["Diminished"]       = {1,0.5,1,0.5,1,0.5,1,0.5};
    m_scales_interval_map["Natural_Minor"]    = {1,0.5,1,1,0.5,1,1};
    m_scales_interval_map["Melodic_Minor"]    = {1,0.5,1,1,1,1,0.5};
    m_scales_interval_map["Harmonic_Minor"]   = {1,0.5,1,1,0.5,1.5,1};
    m_scales_interval_map["Dorian_Scale"]     = {1,0.5,1,1,1,0.5,1};
    m_scales_interval_map["Phrygian_Scale"]   = {0.5,1,1,1,0.5,1,1};
    m_scales_interval_map["Lydian_Scale"]     = {1,1,1,0.5,1,1,0.5};
    m_scales_interval_map["Mixolydian_Scale"] = {1,1,0.5,1,1,0.5,1};
}

void MusicScaleMap::setKeyToFreq()
{
  m_key_to_freq["C"] = 4 * 16.35;
  m_key_to_freq["C#"] = 4 * 17.32;
  m_key_to_freq["D"] = 4 * 18.35;
  m_key_to_freq["D#"] = 4 * 19.45;
  m_key_to_freq["E"] = 4 * 20.60;
  m_key_to_freq["F"] = 4 * 21.83;
  m_key_to_freq["F#"] = 4 * 23.12;
  m_key_to_freq["G"] = 4 * 24.50;
  m_key_to_freq["G#"] = 4 * 25.96;
  m_key_to_freq["A"] = 4 * 27.50;
  m_key_to_freq["A#"] = 4 * 29.14;
  m_key_to_freq["B"] = 4 * 30.87;
}

double MusicScaleMap::getIntervalAsHz(uint input)
{
    int scale_size = m_scales_interval_map[m_current_scale].size();
    double interval{0.0};
    for(int i=0; i<input; ++i)
    {
        std::cout << "(i % scale_size)=("<<i<<"%"<<scale_size<<")="<< (i % scale_size)<< "\n" <<
        "<m_scales_interval_map[m_current_scale].at(i % scale_size)="<<m_scales_interval_map[m_current_scale].at(i % scale_size)<<std::endl;
        interval += m_scales_interval_map[m_current_scale].at(i % scale_size);
    }
    std::cout << "input="<<input<<" |scale_size="<<scale_size<<" |interval="<<interval<<std::endl;
    return calculateFrequency(
        m_key_to_freq[m_current_base_note],
        interval
        );
}

double MusicScaleMap::calculateFrequency(double f0, double tonesAbove) {
    double semitones = tonesAbove * 2;
    double freq = f0 * std::pow(2.0, semitones / 12.0);
    std::cout << "f0 = " << f0 << " | semitones = " << semitones << " | freq =" << freq << "\n";
    return freq;
}

void  MusicScaleMap::setScale(std::string scale)
{
    m_current_scale = scale;
}

void  MusicScaleMap::setKey(std::string key)
{
    m_current_base_note = key;
}