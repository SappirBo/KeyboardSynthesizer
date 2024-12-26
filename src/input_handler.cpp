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

int32_t InputHandler::getCurrentVal()
{
    return m_current_val;
}

void InputHandler::getInputFromUser()
{
    char  value = getch();
    char updated_value = reinterpretInput(value);

    m_current_val = updated_value;
}

char InputHandler::reinterpretInput(const char input)
{
    switch (input)
    {
    case 'q':
        return 'a'+ 0;
        break;
    case 'w':
        return 'a'+ 1;
        break;
    case 'e':
        return 'a'+ 2;
        break;
    case 'r':
        return 'a'+ 3;
        break;
    case 't':
        return 'a'+ 4;
        break;
    case 'y':
        return 'a'+ 5;
        break;
    case 'u':
        return 'a'+ 6;
        break;
    case 'i':
        return 'a'+ 7;
        break;
    case 'o':
        return 'a'+ 8;
        break;
    case 'p':
        return 'a'+ 10;
        break;
    case 'a':
        return 'a'+ 11;
        break;
    case 's':
        return 'a'+ 12;
        break;
    case 'd':
        return 'a'+ 13;
        break;
    case 'f':
        return 'a'+ 14;
        break;
    case 'g':
        return 'a'+ 15;
        break;
    case 'h':
        return 'a'+ 16;
        break;
    case 'j':
        return 'a'+ 17;
        break;
    case 'k':
        return 'a'+ 18;
        break;
    case 'l':
        return 'a'+ 19;
        break;
    case 'z':
        return 'a'+ 20;
        break;
    case 'x':
        return 'a'+ 21;
        break;
    case 'c':
        return 'a'+ 22;
        break;
    case 'v':
        return 'a'+ 23;
        break;
    case 'b':
        return 'a'+ 24;
        break;
    case 'n':
        return 'a'+ 25;
        break;
    case 'm':
        return 'a'+ 26;
        break;
    
    default:
        return input;
    }
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


