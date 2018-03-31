// process.h in Otus Homework #4

#pragma once

#include <iostream>
#include "is_suitable_container.h"
#include <cmath>

template<typename T>
void print_ip (std::ostream& outputStream,
               typename std::enable_if<std::is_integral<T>::value, T>::type input_value)
{
  for (int idx{sizeof(T) - 1}; idx >= 0; idx--)
  {
    int octet{static_cast<uint8_t>(input_value >> (8 * idx))};
    outputStream << ( octet );
    if (idx != 0)
      outputStream << ".";
  }
  outputStream << std::endl;
}

template<typename T>
void print_ip (std::ostream& outputStream,
               typename std::enable_if<is_suitable_container<T>::value, T>::type input_value)
{
  for (auto& item : input_value)
  {
    int octet{static_cast<uint8_t>(item)};
    outputStream << octet;
    if (item != *(input_value).rbegin())
      std::cout << ".";
  }
  outputStream << std::endl;
}

template<typename T>
void print_ip (std::ostream& outputStream,
               typename std::enable_if<std::is_same<T, std::string>::value, T>::type input_value)
{
  outputStream << input_value;
  outputStream << std::endl;
}


template <std::size_t... indices, typename... Types>
auto getTupleTail_Helper(std::index_sequence<indices...>, const std::tuple<Types...>& aTuple)
{
  return std::make_tuple(std::get<indices + 1u>(aTuple)...);
}

template<typename... Types>
auto getTupleTail(const std::tuple<Types...>& aTuple)
{
  return  getTupleTail_Helper(std::make_index_sequence<sizeof...(Types) - 1u>(), aTuple);
}

void printTuple(std::ostream&, const std::tuple<>&);

template<typename HeadType, typename... TailTypes>
void printTuple(std::ostream& outputStream,
                const std::tuple<HeadType, TailTypes...>& aTuple)
{
  int octet{static_cast<uint8_t>(std::get<0>(aTuple))};
  outputStream << octet;
  if (sizeof...(TailTypes) != 0)
      outputStream << ".";
  printTuple(outputStream, getTupleTail(aTuple));
}

template<typename T>
void print_ip (std::ostream& outputStream,
               typename std::enable_if<is_suitable_tuple<T>::value, T>::type input_value)
{
  printTuple(outputStream, input_value);
  outputStream << std::endl;
}

void process(std::ostream& outputStream);
