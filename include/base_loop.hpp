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

    void clearConsole();
    
public:
    BaseLoop() = delete; // delete the defualt constractor

    /** New loop must get pointer to the state machine */
    BaseLoop(std::shared_ptr<SynthState> state);
    ~BaseLoop() = default;

    /** Run the loop */
    virtual void runLoop() = 0;
};
#endif