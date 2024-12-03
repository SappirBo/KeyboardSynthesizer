#include "configure_loop.hpp"

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
    str += "3. Set key and Scale\n";
    str += "4. Back to Main\n";
    str += "5. Exit\n";
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
        *m_state.get() = SynthState::Configure_Key_and_Scale;
        break;
    case '4':
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


void ConfigureLoop::set_key_and_scale_loop()
{
    clear_console();
    std::ostringstream oss;
    oss << "1. Set Key   (current: " << m_synthesizer.get()->getSynthKey() << ")\n";
    oss << "2. Set Scale (current:" << m_synthesizer.get()->getSynthScale() << ")\n";
    oss << "3. Exit\n";
    std::cout << m_line_str << "\n" << oss.str();

    char input;
    std::cin >> input;
    switch (input)
    {
    case '1':{
        *m_state.get() = SynthState::Configure_Key;
        break;
        }
    case '2':{
        *m_state.get() = SynthState::Configure_Scale;
        break;
        }
    default:
        *m_state.get() = SynthState::Defualt;
        break;
    }
}

void ConfigureLoop::set_key_loop()
{
    clear_console();
    std::ostringstream oss;
    oss << "1. C\n" << "2. C#/Db\n" << "3. D\n" << "4. D#/Eb\n" << "5. E\n" << "6. F\n" << "7. F#/Gb\n" ;
    oss << "8. G\n" << "9. G#/Ab\n" << "10. A\n" << "11. A#/Bb\n" << "12. B\n" ;
    oss << "13. Exit\n";
    std::cout << m_line_str << "\n" << oss.str();

    int input;
    std::cin >> input;
    switch (input)
    {
    case 1:{
        m_synthesizer.get()->setSynthKey("C");
        *m_state.get() = SynthState::Configure_Key_and_Scale;
        break;
        }
    case 2:{
        m_synthesizer.get()->setSynthKey("C#");
        *m_state.get() = SynthState::Configure_Key_and_Scale;
        break;
        }
    case 3:{
        m_synthesizer.get()->setSynthKey("D");
        *m_state.get() = SynthState::Configure_Key_and_Scale;
        break;
        }
    case 4:{
        m_synthesizer.get()->setSynthKey("D#");
        *m_state.get() = SynthState::Configure_Key_and_Scale;
        break;
        }
    case 5:{
        m_synthesizer.get()->setSynthKey("E");
        *m_state.get() = SynthState::Configure_Key_and_Scale;
        break;
        }
    case 6:{
        m_synthesizer.get()->setSynthKey("F");
        *m_state.get() = SynthState::Configure_Key_and_Scale;
        break;
        }
    case 7:{
        m_synthesizer.get()->setSynthKey("F#");
        *m_state.get() = SynthState::Configure_Key_and_Scale;
        break;
        }
    case 8:{
        m_synthesizer.get()->setSynthKey("G");
        *m_state.get() = SynthState::Configure_Key_and_Scale;
        break;
        }
    case 9:{
        m_synthesizer.get()->setSynthKey("G#");
        *m_state.get() = SynthState::Configure_Key_and_Scale;
        break;
        }
    case 10:{
        m_synthesizer.get()->setSynthKey("A");
        *m_state.get() = SynthState::Configure_Key_and_Scale;
        break;
        }
    case 11:{
        m_synthesizer.get()->setSynthKey("A#");
        *m_state.get() = SynthState::Configure_Key_and_Scale;
        break;
        }
    case 12:{
        m_synthesizer.get()->setSynthKey("B");
        *m_state.get() = SynthState::Configure_Key_and_Scale;
        break;
        }
    default:
        *m_state.get() = SynthState::Defualt;
        break;
    }
}

void ConfigureLoop::set_scale_loop()
{
    clear_console();
    std::ostringstream oss;
    oss << "1.  major\n" << "2.  Minor_Pentatonic\n" << "3.  Major_Pentatonic\n" << "4.  Blues\n" 
        << "5.  Diminished\n" << "6.  Natural_Minor\n" << "7.  Melodic_Minor\n"  << "8.  Harmonic_Minor\n" 
        << "9.  Dorian_Scale\n" << "10. Phrygian_Scale\n" << "11. Lydian_Scale\n" << "12. Mixolydian_Scale\n" << "13. Exit\n";
    std::cout << m_line_str << "\n" << oss.str();

    int input;
    std::cin >> input;
    switch (input)
    {
    case 1:{
        m_synthesizer.get()->setSynthScale("major");
        *m_state.get() = SynthState::Configure_Key_and_Scale;
        break;
        }
    case 2:{
        m_synthesizer.get()->setSynthScale("Minor_Pentatonic");
        *m_state.get() = SynthState::Configure_Key_and_Scale;
        break;
        }
    case 3:{
        m_synthesizer.get()->setSynthScale("Major_Pentatonic");
        *m_state.get() = SynthState::Configure_Key_and_Scale;
        break;
        }
    case 4:{
        m_synthesizer.get()->setSynthScale("Blues");
        *m_state.get() = SynthState::Configure_Key_and_Scale;
        break;
        }
    case 5:{
        m_synthesizer.get()->setSynthScale("Diminished");
        *m_state.get() = SynthState::Configure_Key_and_Scale;
        break;
        }
    case 6:{
        m_synthesizer.get()->setSynthScale("Natural_Minor");
        *m_state.get() = SynthState::Configure_Key_and_Scale;
        break;
        }
    case 7:{
        m_synthesizer.get()->setSynthScale("Melodic_Minor");
        *m_state.get() = SynthState::Configure_Key_and_Scale;
        break;
        }
    case 8:{
        m_synthesizer.get()->setSynthScale("Harmonic_Minor");
        *m_state.get() = SynthState::Configure_Key_and_Scale;
        break;
        }
    case 9:{
        m_synthesizer.get()->setSynthScale("Dorian_Scale");
        *m_state.get() = SynthState::Configure_Key_and_Scale;
        break;
        }
    case 10:{
        m_synthesizer.get()->setSynthScale("Phrygian_Scale");
        *m_state.get() = SynthState::Configure_Key_and_Scale;
        break;
        }
    case 11:{
        m_synthesizer.get()->setSynthScale("Lydian_Scale");
        *m_state.get() = SynthState::Configure_Key_and_Scale;
        break;
        }
    case 12:{
        m_synthesizer.get()->setSynthScale("Mixolydian_Scale");
        *m_state.get() = SynthState::Configure_Key_and_Scale;
        break;
        }
    default:
        *m_state.get() = SynthState::Defualt;
        break;
    }
}
