// process.h in Otus Homework #4

#pragma once

#include <iostream>
#include "is_suitable_container.h"
#include <cmath>

//! print_ip template for integral types
//! is only enabled if input value is of an integral type
template<typename T>
typename std::enable_if<std::is_integral<T>::value>::type
print_ip (std::ostream& outputStream, T inputValue)
{
  for (int idx{sizeof(T) - 1}; idx >= 0; idx--)
  {
    ///extract octets
    int octet{static_cast<uint8_t>((inputValue >> (8 * idx))&0xFF)};
    outputStream << ( octet );
    if (idx != 0)
      outputStream << ".";
  }
  outputStream << std::endl;
}

//! print_ip template for container types
//! is only enabled if input value is of a suitable type:
//! container and stored data should be suitable for keeping ip addresses
template<typename T>
typename std::enable_if<is_suitable_container<T>::value>::type
print_ip (std::ostream& outputStream, T inputValue)
{
  for (auto& item : inputValue)
  {
    int octet{static_cast<uint8_t>(item)};
    outputStream << octet;
    if (std::addressof(item) != std::addressof(*inputValue.rbegin()))
      outputStream << ".";
  }
  outputStream << std::endl;
}

//! print_ip template for string type
//! is only enabled if input value is of std::string type
template<typename T>
typename std::enable_if<std::is_same<T, std::string>::value>::type
print_ip (std::ostream& outputStream, T inputValue)
{
  /// output as is
  outputStream << inputValue;
  outputStream << std::endl;
}

//!Helper function
//!for extracting data from tuples
template <std::size_t... indices, typename... Types>
auto getTupleTail_Helper(std::index_sequence<indices...>, const std::tuple<Types...>& aTuple)
{
  return std::make_tuple(std::get<indices + 1u>(aTuple)...);
}

//! Helper function
//! for 'cutting' tuple's tail
template<typename... Types>
auto getTupleTail(const std::tuple<Types...>& aTuple)
{
  return  getTupleTail_Helper(std::make_index_sequence<sizeof...(Types) - 1u>(), aTuple);
}

//! print_ip template declaration for tuple type
void printTuple(std::ostream&, const std::tuple<>&);

//! print_ip template for tuple type
//! is only enabled if input value is of asuitable type:
//! tuple types should be the same and
//! this type should be suitable for keeping an ip address
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

//! print_ip template for tuple type
//! template specialization for one member tuple
template<typename T>
typename std::enable_if<is_suitable_tuple<T>::value>::type
print_ip (std::ostream& outputStream,  T inputValue)
{
  printTuple(outputStream, inputValue);
  outputStream << std::endl;
}



void process(std::ostream& outputStream);
