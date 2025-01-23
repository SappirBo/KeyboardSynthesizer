#ifndef CONFIGURE_LOOP_HPP
#define CONFIGURE_LOOP_HPP

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

    void runLoop();
    void setEnvelopLoop();
    
    void setKeyAndScaleLoop();
    void setKeyLoop();
    void setScaleLoop();

    void setOscLoop();
    void addOscLoop();
    void removeOscLoop();
    float get_param_from_user(const std::string param_name, const float min, const float max);
};


#endif