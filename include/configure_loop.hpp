#include <iostream>
#include <memory>
#include <sstream>
#include "base_loop.hpp"
#include "synth_state.hpp"
#include "synthesizer.hpp"

class ConfigureLoop : public BaseLoop
{
private:
    std::shared_ptr<Synthesizer> m_synthesizer;
    const std::string m_space_str{"   "};
    const std::string m_line_str{"--------------------"};
public:
    ConfigureLoop(std::shared_ptr<SynthState> state, std::shared_ptr<Synthesizer> synth);
    ~ConfigureLoop();

    void set_synth_data_stream(const std::ostringstream& oss);

    void run_loop();

    void set_envelop_loop();

    float get_param_from_user(const std::string param_name, const float min, const float max);
};

ConfigureLoop::ConfigureLoop(std::shared_ptr<SynthState> state, std::shared_ptr<Synthesizer> synth)
    : BaseLoop(state), m_synthesizer(synth)
{}

ConfigureLoop::~ConfigureLoop()
{
}


void ConfigureLoop::run_loop()
{
    clear_console();
    std::cout << m_line_str << "\n" << "Synthesizer Configuration:" << std::endl;

    std::ostringstream oss;
    m_synthesizer.get()->getConfigAsStr(oss);
    std::cout << m_line_str << "\n" << oss.str();
    
    std::string str;
    str += "1. Add/ Remove Oscillator\n";
    str += "2. Set Envelope\n";
    str += "3. Back to Main\n";
    str += "4. Exit\n";
    std::cout << m_line_str << "\n" << str;

    char input;
    std::cin >> input;
    switch (input)
    {
    case '1':
        // m_state = SynthState::Play;
        break;
    case '2':
        *m_state.get() = SynthState::Configure_Envelop;
        break;
    case '3':
        *m_state.get() = SynthState::Main;
        break;
    default:
        *m_state.get() = SynthState::Out;
        break;
    }
}

void ConfigureLoop::set_envelop_loop()
{
    clear_console();
    std::ostringstream oss;
    oss << "1. Set Attack  (" << m_synthesizer.get()->get_attack_time() << " seconds)\n";
    oss << "2. Set Decay   (time =" << m_synthesizer.get()->get_decay_time() << " seconds, level = " << m_synthesizer.get()->get_decay_level() << ")\n";
    oss << "3. Set Sustain (" << m_synthesizer.get()->get_sustain_time() << " seconds)\n";
    oss << "4. Set Release (" << m_synthesizer.get()->get_release_time() << " seconds)\n";
    oss << "5. Exit\n";
    std::cout << m_line_str << "\n" << oss.str();

    char input;
    std::cin >> input;
    switch (input)
    {
    case '1':{
        float num = get_param_from_user("Attack Time (seconds)", 0.0, 10000.0);
        m_synthesizer.get()->set_attack_time(num);
        *m_state.get() = SynthState::Configure_Envelop;
        break;
        }
    case '2':{
        float num = get_param_from_user("Decay Time (seconds)", 0.0, 10000.0);
        m_synthesizer.get()->set_decay_time(num);
        num = get_param_from_user("Decay Level ", 0.0, 1.0);
        m_synthesizer.get()->set_decay_level(num);
        *m_state.get() = SynthState::Configure_Envelop;
        break;
        }
    case '3':{
        float num = get_param_from_user("Sustain Time (seconds)", 0.0, 10000.0);
        m_synthesizer.get()->set_sustain_time(num);
        *m_state.get() = SynthState::Configure_Envelop;
        break;
        }
    case '4':{
        float num = get_param_from_user("Release Time (seconds)", 0.0, 10000.0);
        m_synthesizer.get()->set_release_time(num);
        *m_state.get() = SynthState::Configure_Envelop;
        break;
        }
    case '5':{
        *m_state.get() = SynthState::Configure;
        break;
        }
    default:
        *m_state.get() = SynthState::Defualt;
        break;
    }
}


float ConfigureLoop::get_param_from_user(const std::string param_name, const float min, const float max)
{
    clear_console();
    std::ostringstream oss;
    oss << "Please add " << param_name << " [" << min << "-"<<max << "] :\n";
    std::cout << m_line_str << "\n" << oss.str();

    float f;
    std::cin >> f;
    return f;
}
