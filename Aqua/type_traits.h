#pragma once

#include <type_traits>
#if 0
// Note: implementations mostly came from cppreference.com
namespace std {

    // enable_if
    template <bool B, typename T = void>
    struct enable_if {};
    
    template<typename T>
    struct enable_if<true, T> {
        typedef T type;
    };
    
    // is_same
    template <typename T, typename U>
    struct is_same : std::false_type {};

    template <typename T>
    struct is_same<T, T> : std::true_type {};
    
    // is_arithmetic
    template <typename T>
    struct is_arithmetic : std::integral_constant<
        bool,
        std::is_integral<T>::value ||
        std::is_floating_point<T>::value
    > {};    

    // is_signed
    namespace detail {
        template<typename T,bool = std::is_arithmetic<T>::value>
        struct is_signed : std::integral_constant<bool, T(-1) < T(0)> {};

        template<typename T>
        struct is_signed<T,false> : std::false_type {};
    } // namespace detail

    template<typename T>
    struct is_signed : detail::is_signed<T>::type {};    
    
} // namespace std
#endif