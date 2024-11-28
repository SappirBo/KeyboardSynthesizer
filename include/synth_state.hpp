#ifndef SYNTH_STATE_HPP
#define SYNTH_STATE_HPP

/**
 * State machine to hold all the posiable states of the Synth
 */
enum class SynthState{
    Main,
    Play,
    Configure,
    Save_Load,
    Out,
    Defualt
};

#endif