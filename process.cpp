// process.cpp in Otus Homework #4

#include "process.h"

void printTuple(std::ostream&, const std::tuple<>&){}

//! process() function is made for testing purposes
//! it has an output stream as the only argument
//! this allows to test its output
void process(std::ostream& outputStream)
{
  print_ip(outputStream, char{-1}); // <char>

  print_ip(outputStream, short{0}); //<short>

  print_ip(outputStream, 2130706433); //<int>

  print_ip(outputStream, 8875824491850138409); //<long long>

  print_ip(outputStream, std::string{"192.168.11.17.234.99"}); //<std::string>

  print_ip(outputStream, std::vector<int>{124,123,18,0}); //<std::vector<int>>

  print_ip(outputStream, std::tuple<char, char, char, char>{103, 19, 0, -1}); // <std::tuple<char, char, char, char>>
}
