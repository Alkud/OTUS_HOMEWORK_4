// is_suitable_container.h in Otus Homework #4

#pragma once

/* List of container types suitable for keeping an ip address */
#include <array>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <queue>
#include <stack>

/* List of non suitable container types : the are ordered! */
#include <map> // including multimap
#include <set> // including multiset

#include <string>
#include <type_traits>


template <typename T>
struct  is_suitable_container : std::false_type{};

template <typename T, size_t n> struct is_suitable_container<std::array<T, n>> :
std::integral_constant<
                       bool,
                       std::is_integral<T>::value || std::is_same<T, std::string>::value
                      >{};

template <typename T> struct is_suitable_container<std::vector<T>> :
std::integral_constant<
                       bool,
                       std::is_integral<T>::value || std::is_same<T, std::string>::value
                      >{};

template <typename T> struct is_suitable_container<std::list<T>> :
std::integral_constant<
                        bool,
                        std::is_integral<T>::value || std::is_same<T, std::string>::value
                      >{};

template <typename T> struct is_suitable_container<std::forward_list<T>> :
std::integral_constant<
                        bool,
                        std::is_integral<T>::value || std::is_same<T, std::string>::value
                      >{};

template <typename T> struct is_suitable_container<std::deque<T>> :
std::integral_constant<
                        bool,
                        std::is_integral<T>::value || std::is_same<T, std::string>::value
                      >{};

/* Queue is only suitable if its underlying container is suitable */
template <typename T, class Container>
struct  is_suitable_container<std::queue<T, Container>> :
    is_suitable_container<Container>{};

/* Stack is only suitable if its underlying container is suitable */
template <typename T, class Container>
struct  is_suitable_container<std::stack<T, Container>> :
    is_suitable_container<Container>{};

template<typename T, typename T1, typename... Types>
struct are_same :
    std::integral_constant<
                            bool,
                            std::is_same<T, T1>::value && are_same<T1, Types...>::value
                          >{};

template<typename T, typename T1, typename T2>
struct are_same<T, T1, T2> :
    std::integral_constant<
                            bool,
                            std::is_same<T, T1>::value && std::is_same<T1, T2>::value
                          >{};


template<typename T1, typename T2>
struct are_same<T1, T2> :
    std::integral_constant<
                            bool,
                            std::is_same<T1, T2>::value
                          >{};


template <typename T>
struct  is_suitable_tuple : std::false_type{};

template<typename T>
struct is_suitable_tuple< std::tuple<std::vector<T, std::allocator<T>>> > :
std::integral_constant<
                       bool,
                       std::is_integral<T>::value || std::is_same<T, std::string>::value
                      > {};

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
