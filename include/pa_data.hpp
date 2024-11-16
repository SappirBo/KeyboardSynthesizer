#ifndef PA_DATA_HPP
#define PA_DATA_HPP

#include <iostream>
#include "audio_settings.hpp"

typedef struct
{
    float wave_table[AudioSettings::TABLE_SIZE];
    float left_phase;
    float right_phase;
    float phaseIncrement;
    char message[20];
}
paData;



#endif