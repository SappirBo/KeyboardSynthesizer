#ifndef SYNTH_STATE_HPP
#define SYNTH_STATE_HPP

/**
 * State machine to hold all the posiable states of the Synth
 */
enum class SynthState{
    Main,
    Play,
    Configure,
    Configure_OSC,
    Configure_Envelop,
    Configure_Key,
    Configure_Scale,
    Configure_Key_and_Scale,
    Save_Load,
    Out,
    Defualt
};

#endif