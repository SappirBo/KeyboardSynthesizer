#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <iostream>
#include <termios.h>
#include <unistd.h>

class InputHandler
{
private:
    int32_t m_current_val{-1};
    struct termios m_old_termios;  // Store old terminal settings
    char getch();

    void startNonCanonicalInput();
    void endNonCanonicalInput();

public:
    InputHandler();
    ~InputHandler();
    
    void getInputFromUser();
    int32_t getCurrentVal();

    char reinterpretInput(const char input);

    bool operator>(const int32_t& other) const;
    bool operator>=(const int32_t& other) const;
    bool operator<(const int32_t& other) const;
    bool operator<=(const int32_t& other) const;
    bool operator==(const int32_t& other) const;

    void inputHandlerOn(){startNonCanonicalInput();};   
    void inputHandlerOff(){endNonCanonicalInput();};    
};


#endif