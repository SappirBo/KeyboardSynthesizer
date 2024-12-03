#ifndef MUSIC_SCALE_HPP
#define MUSIC_SCALE_HPP

#include <cmath>
#include <vector>
#include <unordered_map>
#include <string>

class MusicScaleMap
{
private:
    //ToDo: change the vector type to - Note, that will be in 0.5 intervals;
    std::unordered_map<std::string, std::vector<double>> m_scales_interval_map;
    std::unordered_map<std::string, float> m_key_to_freq;
    
    std::string m_current_scale;
    std::string m_current_base_note;

    void setKeyToFreq();

    /***  Convert tones to semitones */
    double calculateFrequency(double, double);
    
    /** sets map with the intervals*/
    void setScaleIntervalsMap();


public:
    MusicScaleMap();
    ~MusicScaleMap();

    /**
     * tranfer input to Hz
     * @params: input as num 0-25
     */
    double getIntervalAsHz(uint); 

    void setScale(std::string);

    void setKey(std::string);
};
#endif
