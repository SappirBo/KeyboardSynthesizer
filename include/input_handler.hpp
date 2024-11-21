#include <iostream>
#include <termios.h>
#include <unistd.h>

class InputHandler
{
private:
    int32_t m_current_val{-1}; 

    char getch();

public:
    InputHandler();
    ~InputHandler();
    
    void get_input_from_user();
    int32_t get_current_val();

    bool operator>(const int32_t& other) const;
    bool operator>=(const int32_t& other) const;
    bool operator<(const int32_t& other) const;
    bool operator<=(const int32_t& other) const;
    bool operator==(const int32_t& other) const;
};


