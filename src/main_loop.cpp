#include "main_loop.hpp"


MainLoop::MainLoop(std::shared_ptr<SynthState> state): BaseLoop(state){}

MainLoop::~MainLoop(){}

void MainLoop::runLoop()
{
    clearConsole();
    std::string str;
    str += "    1. Play\n";
    str += "    2. Configure Synth\n";
    str += "    3. Save / Load Preset\n";
    str += "    4. Out\n";
    std::cout << str;

    char input;
    std::cin >> input; 
    switch (input)
    {
    case '1':
        *(m_state.get()) = SynthState::Play;
        break;
    case '2':
        *(m_state.get()) = SynthState::Configure;
        break;
    case '3':
        *(m_state.get()) = SynthState::Save_Load;
        break;
    case '4':
        *(m_state.get()) = SynthState::Out;
        break;
    default:
        *(m_state.get()) = SynthState::Defualt;
        break;
    }
}
