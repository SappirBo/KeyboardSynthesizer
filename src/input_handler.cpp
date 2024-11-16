#include "input_handler.hpp"


InputHandler::InputHandler(/* args */)
{
}

InputHandler::~InputHandler()
{
}

int InputHandler::get_current_val()
{
    return m_current_val;
}

void InputHandler::get_input_from_user()
{
    m_current_val = getch();
}

char InputHandler::getch() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(STDIN_FILENO, &old) < 0)
        perror("tcgetattr()");
    old.c_lflag &= ~ICANON;  // Disable canonical mode
    old.c_lflag &= ~ECHO;    // Disable echo
    if (tcsetattr(STDIN_FILENO, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(STDIN_FILENO, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;   // Re-enable canonical mode
    old.c_lflag |= ECHO;     // Re-enable echo
    if (tcsetattr(STDIN_FILENO, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}

bool InputHandler::operator>(const int& other) const
{
    return m_current_val > other;
}

bool InputHandler::operator>=(const int& other) const
{
    return m_current_val >= other;
}

bool InputHandler::operator<(const int& other) const
{
    return m_current_val < other;
}

bool InputHandler::operator<=(const int& other) const
{
    return m_current_val <= other;
}

bool InputHandler::operator==(const int& other) const
{
    return m_current_val == other;
}


