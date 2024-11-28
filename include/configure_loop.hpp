#include <iostream>
#include <memory>
#include <sstream>
#include "base_loop.hpp"
#include "synth_state.hpp"


class ConfigureLoop : public BaseLoop
{
private:
    std::ostringstream m_synth_data_as_str;
public:
    ConfigureLoop(std::shared_ptr<SynthState> state);
    ~ConfigureLoop();

    void set_synth_data_stream(const std::ostringstream& oss);

    void run_loop();
};

ConfigureLoop::ConfigureLoop(std::shared_ptr<SynthState> state)
    : BaseLoop(state)
{
    m_synth_data_as_str << "";
}

ConfigureLoop::~ConfigureLoop()
{
}

void ConfigureLoop::set_synth_data_stream(const std::ostringstream& oss)
{
    m_synth_data_as_str << oss.str();
}

void ConfigureLoop::run_loop()
{
    clear_console();
    std::cout << "Synthesizer Configuration:" << std::endl;

    // std::ostringstream oss;
    // m_synthesizer.get()->getConfigAsStr(oss);
    std::cout << m_synth_data_as_str.str();
    
    std::string str;
    str += "1. Add/ Remove Oscillator\n";
    str += "2. Set Envelope\n";
    str += "3. Set Envelope\n";
    str += "4. Exit\n";
    std::cout << str;

    char input;
    std::cin >> input;
    switch (input)
    {
    case '1':
        // m_state = SynthState::Play;
        break;
    case '2':
        // m_state = SynthState::Configure;
        break;
    case '3':
        *m_state.get() = SynthState::Defualt;
        break;
    case '4':
        *m_state.get() = SynthState::Defualt;
        break;
    default:
        *m_state.get() = SynthState::Defualt;
        break;
    }
}
