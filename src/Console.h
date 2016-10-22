#ifndef CONSOLE_H
#define CONSOLE_H

#include <fstream>

enum LEVEL {
    ERROR,
    WARN,
    INFO,
    DEBUG,
    FINEST
};

class Console {
public:
    static std::ostream& out(int log_level = 0);
    Console(const Console&) = delete;
    Console& operator=(const Console&) = delete;

    static unsigned int LOG_LEVEL;

private:
    Console();
    ~Console();
    std::ofstream m_file;
};

#endif
