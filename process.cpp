// process.cpp in Otus Homework #4

#include "process.h"

void printTuple(std::ostream&, const std::tuple<>&)
{}

void process(std::ostream& outputStream)
{
  print_ip<char>(outputStream, char{-1});

  print_ip<short>(outputStream, short{0});

  print_ip<int>(outputStream, 2130706433);

  print_ip<long long>(outputStream, 8875824491850138409);

  print_ip<std::string>(outputStream, "192.168.11.17.234.99");

  print_ip<std::vector<int>>(outputStream, std::vector<int>{124,123,18,0});

  print_ip<std::tuple<char, char, char, char>>(outputStream, std::tuple<char, char, char, char>{103, 19, 0, -1});
}
