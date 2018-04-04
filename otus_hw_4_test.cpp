// otus_hw_4_test.cpp in Otus Homework #4

#define BOOST_TEST_MODULE OTUS_HW_4_TEST

#include <boost/test/unit_test.hpp>
#include "process.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <numeric>


BOOST_AUTO_TEST_SUITE(homework_4_test)

BOOST_AUTO_TEST_CASE(check_output_with_char)
{
  std::cout << std::endl << "CHECK_CHAR_ADDRESS" << std::endl;

  std::stringstream receiveStream{};

  std::vector<int> testIntegers{};
  std::vector<char> testAddresses{};

  char b0{};
  for (size_t inputStringIdx{}; inputStringIdx < 255; inputStringIdx++)
  {
    b0 = inputStringIdx - 127;
    testIntegers.push_back(b0);
    testAddresses.push_back(b0);
    print_ip(receiveStream, b0);
  }

  size_t errorsCount{};
  auto iterA{testAddresses.begin()};
  auto iterI{testIntegers.begin()};
  std::string nextString{};
  while(std::getline(receiveStream, nextString) && iterA != testAddresses.end() && iterI != testIntegers.end())
  {
//      std::cout << *iterI << " -> " <<
//                   nextString <<
//                   " -> " << static_cast<int>(static_cast<uint8_t>(*iterA)) <<
//                   std::endl;
    if (std::stoi(nextString) != static_cast<uint8_t>(*iterI))
        errorsCount++;
    iterA++; iterI++;
  }

  BOOST_CHECK(errorsCount == 0);
}

BOOST_AUTO_TEST_CASE(check_output_with_short)
{
  std::cout << std::endl << "CHECK_SHORT_ADDRESS" << std::endl;

  std::stringstream receiveStream{};

  std::vector<std::string> testStrings{};
  std::vector<short> testAddresses{};

  uint8_t b0{};
  uint8_t b1{};
  short address{};
  for (size_t inputStringIdx{}; inputStringIdx < 128; inputStringIdx++)
  {
    b0 = inputStringIdx;
    b1 = 127 - inputStringIdx;
    address = b1 << 8 | b0;
    testStrings.push_back(std::to_string(b1) + std::string{"."} + std::to_string(b0));
    testAddresses.push_back(address);
    print_ip(receiveStream, address);
  }

  size_t errorsCount{};
  auto iterA{testAddresses.begin()};
  auto iterS{testStrings.begin()};
  std::string nextString{};
  while(std::getline(receiveStream, nextString) && iterA != testAddresses.end() && iterS != testStrings.end())
  {
//    std::cout << *iterS << " -> " << *iterA << " -> " << nextString << std::endl;
    if (nextString != *iterS)
        errorsCount++;
    iterA++; iterS++;
  }
  BOOST_CHECK(errorsCount == 0);
}

BOOST_AUTO_TEST_CASE(check_output_with_int)
{
  std::cout << std::endl << "CHECK_INT_ADDRESS" << std::endl;

  std::stringstream receiveStream{};

  std::vector<std::string> testStrings{};
  std::vector<int> testAddresses{};

  uint8_t b0{};
  uint8_t b1{};
  uint8_t b2{};
  uint8_t b3{};
  int address{};
  for (size_t inputStringIdx{}; inputStringIdx < 128; inputStringIdx++)
  {
    b0 = inputStringIdx;
    b1 = inputStringIdx + 128;
    b2 = 255 - inputStringIdx;
    b3 = 127 - inputStringIdx;
    address = b3 << 24 | b2 << 16 | b1 << 8 | b0;
    testStrings.push_back(std::to_string(b3) + std::string{"."}
                          + std::to_string(b2) + std::string{"."}
                          + std::to_string(b1) + std::string{"."} + std::to_string(b0));
    testAddresses.push_back(address);
    print_ip(receiveStream, address);
  }

  size_t errorsCount{};
  auto iterA{testAddresses.begin()};
  auto iterS{testStrings.begin()};
  std::string nextString{};
  while(std::getline(receiveStream, nextString) && iterA != testAddresses.end() && iterS != testStrings.end())
  {
//    std::cout << *iterS << " -> " << *iterA << " -> " << nextString << std::endl;
    if (nextString != *iterS)
        errorsCount++;
    iterA++; iterS++;
  }
  BOOST_CHECK(errorsCount == 0);
}

BOOST_AUTO_TEST_CASE(check_output_with_long)
{
  std::cout << std::endl << "CHECK_LONG_ADDRESS" << std::endl;

  std::stringstream receiveStream{};

  std::vector<std::string> testStrings{};
  std::vector<long long> testAddresses{};

  uint64_t b0{};
  uint64_t b1{};
  uint64_t b2{};
  uint64_t b3{};
  uint64_t b4{};
  uint64_t b5{};
  uint64_t b6{};
  uint64_t b7{};
  long long address{};
  for (size_t inputStringIdx{}; inputStringIdx < 127; inputStringIdx++)
  {
    b0 = 255 -inputStringIdx;
    b1 = inputStringIdx + 127;
    b2 = 200 - inputStringIdx;
    b3 = inputStringIdx + 15;
    b4 = 185 -inputStringIdx;
    b5 = inputStringIdx + 32;
    b6 = 127 - inputStringIdx;
    b7 = inputStringIdx;
    address = (b7 << 56) | (b6 << 48) | (b5 << 40) | (b4 << 32) | (b3 << 24) | (b2 << 16) | (b1 << 8) | b0;
    testStrings.push_back(  std::to_string(b7) + std::string{"."}
                          + std::to_string(b6) + std::string{"."}
                          + std::to_string(b5) + std::string{"."}
                          + std::to_string(b4) + std::string{"."}
                          + std::to_string(b3) + std::string{"."}
                          + std::to_string(b2) + std::string{"."}
                          + std::to_string(b1) + std::string{"."} + std::to_string(b0));
    testAddresses.push_back(address);
    print_ip<long long>(receiveStream, address);
  }

  size_t errorsCount{};
  auto iterA{testAddresses.begin()};
  auto iterS{testStrings.begin()};
  std::string nextString{};
  while(std::getline(receiveStream, nextString) && iterA != testAddresses.end() && iterS != testStrings.end())
  {
//    std::cout << *iterS << " -> " << *iterA << " -> " << nextString << std::endl;
    if (nextString != *iterS)
       errorsCount++;
    iterA++; iterS++;
  }
  BOOST_CHECK(errorsCount == 0);
}

BOOST_AUTO_TEST_CASE(check_output_with_string)
{
  std::cout << std::endl << "CHECK_LONG_ADDRESS" << std::endl;

  std::stringstream receiveStream{};

  std::vector<std::string> testStrings{};

  uint64_t b0{};
  uint64_t b1{};
  uint64_t b2{};
  uint64_t b3{};
  uint64_t b4{};
  uint64_t b5{};
  uint64_t b6{};
  uint64_t b7{};
  std::string address{};
  for (size_t inputStringIdx{}; inputStringIdx < 127; inputStringIdx++)
  {
    b0 = 255 -inputStringIdx;
    b1 = inputStringIdx + 127;
    b2 = 200 - inputStringIdx;
    b3 = inputStringIdx + 15;
    b4 = 185 -inputStringIdx;
    b5 = inputStringIdx + 32;
    b6 = 127 - inputStringIdx;
    b7 = inputStringIdx;

    address =   std::to_string(b7) + std::string{"."}
              + std::to_string(b6) + std::string{"."}
              + std::to_string(b5) + std::string{"."}
              + std::to_string(b4) + std::string{"."}
              + std::to_string(b3) + std::string{"."}
              + std::to_string(b2) + std::string{"."}
              + std::to_string(b1) + std::string{"."} + std::to_string(b0);
    testStrings.push_back(address);
    print_ip<std::string>(receiveStream, address);
  }

  size_t errorsCount{};
  auto iterS{testStrings.begin()};
  std::string nextString{};
  while(std::getline(receiveStream, nextString) && iterS != testStrings.end())
  {
//    std::cout << *iterS << " -> " << nextString << std::endl;
    if (nextString != *iterS)
       errorsCount++;
    iterS++;
  }
  BOOST_CHECK(errorsCount == 0);
}

BOOST_AUTO_TEST_CASE(check_output_with_vector)
{
  std::cout << std::endl << "CHECK_VECTOR_ADDRESS" << std::endl;

  std::stringstream receiveStream{};

  std::vector<std::string> testStrings{};

  uint64_t b0{};
  uint64_t b1{};
  uint64_t b2{};
  uint64_t b3{};
  uint64_t b4{};
  uint64_t b5{};
  uint64_t b6{};
  uint64_t b7{};
  std::vector<int> vector{};
  std::string address{};
  for (size_t inputStringIdx{}; inputStringIdx < 127; inputStringIdx++)
  {
    b0 = 255 -inputStringIdx;
    b1 = inputStringIdx + 127;
    b2 = 200 - inputStringIdx;
    b3 = inputStringIdx + 15;
    b4 = 185 -inputStringIdx;
    b5 = inputStringIdx + 32;
    b6 = 127 - inputStringIdx;
    b7 = inputStringIdx;

    address =   std::to_string(b7) + std::string{"."}
              + std::to_string(b6) + std::string{"."}
              + std::to_string(b5) + std::string{"."}
              + std::to_string(b4) + std::string{"."}
              + std::to_string(b3) + std::string{"."}
              + std::to_string(b2) + std::string{"."}
              + std::to_string(b1) + std::string{"."} + std::to_string(b0);

    vector = std::vector<int>{b7, b6, b5, b4, b3, b2, b1, b0};
    testStrings.push_back(address);
    print_ip(receiveStream, vector);
  }

  size_t errorsCount{};
  auto iterS{testStrings.begin()};
  std::string nextString{};
  while(std::getline(receiveStream, nextString) && iterS != testStrings.end())
  {
//    std::cout << *iterS << " -> " << nextString << std::endl;
    if (nextString != *iterS)
      errorsCount++;

    iterS++;
  }
  BOOST_CHECK(errorsCount == 0);
}

BOOST_AUTO_TEST_CASE(check_output_with_tuple)
{
  std::cout << std::endl << "CHECK_TUPLE_ADDRESS" << std::endl;

  std::stringstream receiveStream{};

  std::vector<std::string> testStrings{};

  int b0{};
  int b1{};
  int b2{};
  int b3{};
  int b4{};
  int b5{};
  int b6{};
  int b7{};
  std::tuple<int,int,int,int,int,int,int,int> tuple{};
  std::string address{};
  for (size_t inputStringIdx{}; inputStringIdx < 127; inputStringIdx++)
  {
    b0 = 255 -inputStringIdx;
    b1 = inputStringIdx + 127;
    b2 = 200 - inputStringIdx;
    b3 = inputStringIdx + 15;
    b4 = 185 -inputStringIdx;
    b5 = inputStringIdx + 32;
    b6 = 127 - inputStringIdx;
    b7 = inputStringIdx;

    address =   std::to_string(b7) + std::string{"."}
              + std::to_string(b6) + std::string{"."}
              + std::to_string(b5) + std::string{"."}
              + std::to_string(b4) + std::string{"."}
              + std::to_string(b3) + std::string{"."}
              + std::to_string(b2) + std::string{"."}
              + std::to_string(b1) + std::string{"."} + std::to_string(b0);

    tuple = std::tuple<int,int,int,int,int,int,int,int>{b7, b6, b5, b4, b3, b2, b1, b0};
    testStrings.push_back(address);
    print_ip(receiveStream, tuple);
  }

  size_t errorsCount{};
  auto iterS{testStrings.begin()};
  std::string nextString{};
  while(std::getline(receiveStream, nextString) && iterS != testStrings.end())
  {
//    std::cout << *iterS << " -> " << nextString << std::endl;
    if (nextString != *iterS)
      errorsCount++;

    iterS++;
  }
  BOOST_CHECK(errorsCount == 0);
}

BOOST_AUTO_TEST_CASE(check_output_homework)
{
  std::cout << std::endl << "CHECK_HOMEWORK" << std::endl;

  std::stringstream receiveStream{};

  std::vector<std::string> testStrings{};

  print_ip(receiveStream, char{-1});
  testStrings.push_back(std::string{"255"});
  print_ip(receiveStream, short{0});
  testStrings.push_back(std::string{"0.0"});
  print_ip(receiveStream, 2130706433);
  testStrings.push_back(std::string{"127.0.0.1"});
  print_ip(receiveStream, 8875824491850138409);
  testStrings.push_back(std::string{"123.45.67.89.101.112.131.41"});
  print_ip(receiveStream,std::string{"192.168.11.17.234.99"});
  testStrings.push_back(std::string{"192.168.11.17.234.99"});
  print_ip(receiveStream, std::vector<int>{124,123,18,0});
  testStrings.push_back(std::string{"124.123.18.0"});
  print_ip(receiveStream, std::tuple<char, char, char, char>{103, 19, 0, -1});
  testStrings.push_back(std::string{"103.19.0.255"});

  size_t errorsCount{};
  auto iterS{testStrings.begin()};
  std::string nextString{};
  while(std::getline(receiveStream, nextString) && iterS != testStrings.end())
  {
//    std::cout << *iterS << " -> " << nextString << std::endl;
    if (nextString != *iterS)
      errorsCount++;

    iterS++;
  }
  BOOST_CHECK(errorsCount == 0);
}

BOOST_AUTO_TEST_SUITE_END()
