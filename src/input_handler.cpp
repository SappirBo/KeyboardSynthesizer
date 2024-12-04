#include "input_handler.hpp"


InputHandler::InputHandler()
{
    // Get current terminal settings
    if (tcgetattr(STDIN_FILENO, &m_old_termios) < 0)
        perror("tcgetattr()");

    // Modify terminal settings for non-canonical input without echo
    struct termios new_termios = m_old_termios;
    new_termios.c_lflag &= ~ICANON;
    new_termios.c_lflag &= ~ECHO;

    // Apply new terminal settings
    if (tcsetattr(STDIN_FILENO, TCSANOW, &new_termios) < 0)
        perror("tcsetattr ICANON");
}

InputHandler::~InputHandler()
{
    // Restore old terminal settings
    if (tcsetattr(STDIN_FILENO, TCSANOW, &m_old_termios) < 0)
        perror("tcsetattr ~ICANON");
}



int32_t InputHandler::get_current_val()
{
    return m_current_val;
}

void InputHandler::get_input_from_user()
{
    m_current_val = getch();
}

char InputHandler::getch() {
    char buf = 0;
    if (read(STDIN_FILENO, &buf, 1) < 0)
        perror("read()");
    return buf;
}

bool InputHandler::operator>(const int32_t& other) const
{
    return m_current_val > other;
}

bool InputHandler::operator>=(const int32_t& other) const
{
    return m_current_val >= other;
}

bool InputHandler::operator<(const int32_t& other) const
{
    return m_current_val < other;
}

bool InputHandler::operator<=(const int32_t& other) const
{
    return m_current_val <= other;
}

bool InputHandler::operator==(const int32_t& other) const
{
    return m_current_val == other;
}


