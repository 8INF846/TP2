#include <iostream>
#include "Console.h"


unsigned int Console::LOG_LEVEL = LEVEL::FINEST;;

Console::Console() : m_file("log.txt", std::ios::out) {}

Console::~Console() {
    m_file.close();
}

std::ostream& Console::out(int log_level) {
    static Console c;
    if(log_level > Console::LOG_LEVEL) {
        return c.m_file;
    }
    return std::cout;
}
