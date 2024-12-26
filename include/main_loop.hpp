#ifndef MAIN_LOOP_HPP
#define MAIN_LOOP_HPP

#include <iostream>
#include <memory>
#include "base_loop.hpp"
#include "synth_state.hpp"

class MainLoop: public BaseLoop
{
private:
    /* data */
public:
    MainLoop(std::shared_ptr<SynthState> state);
    ~MainLoop();
    void runLoop();
};


#endif