#ifndef BASE_LOOP_HPP
#define BASE_LOOP_HPP

#include "synth_state.hpp"
#include <memory>
#include <cstdlib> 


class BaseLoop
{
private:
    
protected:
    std::shared_ptr<SynthState> m_state;

    void clear_console();
    
public:
    BaseLoop() = delete; // delete the defualt constractor

    /** New loop must get pointer to the state machine */
    BaseLoop(std::shared_ptr<SynthState> state);
    ~BaseLoop() = default;

    /** Run the loop */
    virtual void run_loop() = 0;
};

BaseLoop::BaseLoop(std::shared_ptr<SynthState> state): m_state(state) {}

void BaseLoop::clear_console()
{
    system("clear");
}

#endif