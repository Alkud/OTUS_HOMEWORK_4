// is_suitable_container.h in Otus Homework #4

#pragma once

//! List of container types suitable for keeping an ip address */
#include <array>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <queue>
#include <stack>

//! List of non suitable container types : the are ordered! */
#include <map> /// including multimap
#include <set> /// including multiset

#include <string>
#include <type_traits>

template <typename T>
struct  is_suitable_container : std::false_type{};

//! array type check template
//! there are two conditions one of wich should be met:
//! inner type is integral OR is std::string
template <typename T, size_t n> struct is_suitable_container<std::array<T, n>> :
std::integral_constant<
                       bool,
                       std::is_integral<T>::value || std::is_same<T, std::string>::value
                      >{};

//! vector type check template
//! there are two conditions one of wich should be met:
//! inner type is integral OR is std::string
template <typename T> struct is_suitable_container<std::vector<T>> :
std::integral_constant<
                       bool,
                       std::is_integral<T>::value || std::is_same<T, std::string>::value
                      >{};

//! list type check template
//! there are two conditions one of wich should be met:
//! inner type is integral OR is std::string
template <typename T> struct is_suitable_container<std::list<T>> :
std::integral_constant<
                        bool,
                        std::is_integral<T>::value || std::is_same<T, std::string>::value
                      >{};

//! forward list type check template
//! there are two conditions one of wich should be met:
//! inner type is integral OR is std::string
template <typename T> struct is_suitable_container<std::forward_list<T>> :
std::integral_constant<
                        bool,
                        std::is_integral<T>::value || std::is_same<T, std::string>::value
                      >{};

//! deque type check template
//! there are two conditions one of wich should be met:
//! inner type is integral OR is std::string
template <typename T> struct is_suitable_container<std::deque<T>> :
std::integral_constant<
                        bool,
                        std::is_integral<T>::value || std::is_same<T, std::string>::value
                      >{};

//! Queue type check template
//! there are two conditions, and BOTH should be met:
//! the underlying container is suitable AND
//! the inner type is integral OR is std::string
template <typename T, class Container>
struct  is_suitable_container<std::queue<T, Container>> :
    is_suitable_container<Container>{};

//! Stack type check template
//! there are two conditions, and BOTH should be met:
//! the underlying container is suitable AND
//! the inner type is integral OR is std::string
template <typename T, class Container>
struct  is_suitable_container<std::stack<T, Container>> :
    is_suitable_container<Container>{};

//! Meta function to check
//! if multiple types are the same (general case)
//! just uses std::is_same and recursion
template<typename T, typename T1, typename... Types>
struct are_same :
    std::integral_constant<
                            bool,
                            std::is_same<T, T1>::value && are_same<T1, Types...>::value
                          >{};

//! are_same template specialization
//! for three mebers case
template<typename T, typename T1, typename T2>
struct are_same<T, T1, T2> :
    std::integral_constant<
                            bool,
                            std::is_same<T, T1>::value && std::is_same<T1, T2>::value
                          >{};


//! are_same template specialization
//! for two mebers case
template<typename T1, typename T2>
struct are_same<T1, T2> :
    std::integral_constant<
                            bool,
                            std::is_same<T1, T2>::value
                          >{};

//! Tuple check specialization template
//! for the common case
template <typename T>
struct  is_suitable_tuple : std::false_type{};

//! Tuple check specialization template
//! for a tuple containing a vector
template<typename T>
struct is_suitable_tuple< std::tuple<std::vector<T, std::allocator<T>>> > :
std::integral_constant<
                       bool,
                       std::is_integral<T>::value || std::is_same<T, std::string>::value
                      > {};

//! Tuple check general template
//! there are two conditions, and BOTH should be met:
//! tuple types are THE SAME
//! the this type is integral OR is std::string
template<typename T, typename... Types>
struct is_suitable_tuple< std::tuple<T,Types...> > :
std::integral_constant<
                        bool,
                        are_same<T, Types...>::value &&
                        (std::is_integral<T>::value || std::is_same<T, std::string>::value)
                      > {};


static_assert(is_suitable_container<std::vector<std::string>>::value == true);

static_assert(is_suitable_container<std::vector<int>>::value == true);

static_assert(is_suitable_container<std::vector<std::vector<int>>>::value == false);

static_assert(is_suitable_container<std::string>::value == false);

static_assert(is_suitable_container<std::queue<int, std::map<int, int>>>::value == false);

static_assert(is_suitable_container<std::stack<int, std::multiset<double>>>::value == false);

static_assert (are_same<int, int, int, int, int>::value == true);

static_assert (are_same<int, int, int, int, float>::value == false);

static_assert (are_same<std::string, std::string, std::string, std::string, std::string>::value == true);

static_assert (are_same<std::string, std::string, std::string, std::string, bool>::value == false);

static_assert (is_suitable_tuple<std::tuple<std::string, std::string, bool>>::value == false);

static_assert (is_suitable_tuple<std::tuple<int, int, int>>::value == true);
