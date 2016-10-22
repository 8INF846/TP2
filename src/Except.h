#ifndef EXCEPT_H
#define EXCEPT_H

#include <exception>
#include <string>

struct Except : public std::exception
{
   std::string s;
   Except(std::string ss) : s(ss) {}
   ~Except() throw () {} // Updated
   const char* what() const throw() { return s.c_str(); }
};

#endif
