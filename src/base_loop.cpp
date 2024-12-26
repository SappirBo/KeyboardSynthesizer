#include "base_loop.hpp"

BaseLoop::BaseLoop(std::shared_ptr<SynthState> state): m_state(state) {}

void BaseLoop::clearConsole()
{
    system("clear");
}
