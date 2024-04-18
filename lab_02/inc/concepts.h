#ifndef __CONCEPTS_HPP__
#define __CONCEPTS_HPP__

#include <ostream>
#include <concepts>

template<typename T>
concept Summable = requires (T a, T b) {
    {a + b} -> std::same_as<T>;
};

template<typename T>
concept Multable = requires (T a, T b) {
    {a * b} -> std::same_as<T>;
};

template<typename T>
concept Divable = requires (T a, T b) {
    {a / b} -> std::same_as<T>;
    {b / a} -> std::same_as<T>;
    // (a / b) * (b / a) == T(1); 
};

template<typename T>
concept Empty = requires { T(); };

template<typename T>
concept Neitral = requires { T(0); };

template<typename T>
concept Сommutativity = requires (T a, T b) {
    a + b == b + a;
};

template<typename T>
concept Comparable = requires (T a, T b) {
    {a == b} -> std::convertible_to<bool>;
    {a != b} -> std::convertible_to<bool>;
    // {!a} -> std::convertible_to<bool>;
    // !a == (a == T(0));
};

template<typename T, typename U>
concept Convertable = requires (T a, U b) {
    { T(b) } -> std::same_as<T>; 
    { U(a) } -> std::same_as<U>;
};

template<typename T>
concept Incrementable = requires (T a) {
    { a++ } -> std::same_as<T>;
    { ++a } -> std::same_as<T&>;
};

template <typename C>
concept ContainerClass = requires (C c) {
    typename C::value_type;
    typename C::size_type;
    
    typename C::iterator;
    typename C::const_iterator;

    { c.begin() } noexcept -> std::same_as<typename C::iterator>;
    { c.end() } noexcept -> std::same_as<typename C::iterator>;

    { c.cend() } noexcept -> std::same_as<typename C::const_iterator>;
    { c.cbegin() } noexcept -> std::same_as<typename C::const_iterator>;
    
    { c.size() } noexcept -> std::same_as<typename C::size_type>;
};

template <typename Iter, typename T>
concept IteratorCheck = Incrementable<Iter> && Comparable<Iter> && 
requires (Iter it) {
    { *it } -> std::convertible_to<const T&>;
};

template <typename T>
concept Printable = requires (T a, std::ostream os) { os << a; };

#endif // __CONCEPTS_HPP__