#include "oscillator.hpp"

class Synthesizer
{
private:
    std::vector<Oscillator> m_osc_vec;
public:
    Synthesizer();
    ~Synthesizer();
};

Synthesizer::Synthesizer(){}

Synthesizer::~Synthesizer(){}
